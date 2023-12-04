#pragma once
#include <jni.h>
#include <jvmti.h>

#include <mutex>
#include <unordered_map>
#include <string>
#include <iostream>

class Lunar
{
public:
    JNIEnv* env;
    JavaVM* vm;
    jvmtiEnv* jvmti;
    std::mutex mutex_;
    Lunar(JNIEnv* env_, JavaVM* vm_) : env(env_), vm(vm_)
    {
        jint res;
        res = vm->GetEnv((void**)&jvmti, JVMTI_VERSION_1_2);
        if (res != JNI_OK)
        {
            // handle error
            std::cout << "Unable to access JVMTI Version 1.2." << std::endl;
            return;
        }

        // check if jvmti is NULL here, which indicates an error
        if (jvmti == NULL)
        {
            std::cout << "Unable to initialize JVMTI." << std::endl;
            return;
        }
    }

    void GetLoadedClasses()
    {
        // Provide thread safety using a mutex.
        std::lock_guard<std::mutex> lock(mutex_);

        jclass* classesPtr;
        jint amount;

        jvmtiError error = jvmti->GetLoadedClasses(&amount, &classesPtr);
        if (error != JVMTI_ERROR_NONE)
        {
            std::cout << "Cannot access loaded classes information." << std::endl;
            return;
        }

        jclass lang = env->FindClass("java/lang/Class");
        if (lang == nullptr)
        {
            std::cout << "Cannot find java/lang/Class." << std::endl;
            return;
        }

        jmethodID getName = env->GetMethodID(lang, "getName", "()Ljava/lang/String;");
        if (getName == nullptr)
        {
            std::cout << "Cannot find getName method." << std::endl;
            return;
        }

        for (jint i = 0; i < amount; ++i)
        {
            jstring name = (jstring)env->CallObjectMethod(classesPtr[i], getName);
            if (name == nullptr)
            {
                continue;
            }

            const char* className = env->GetStringUTFChars(name, 0);
            if (className == nullptr)
            {
                continue;
            }

            std::string classNameStr = className;
            env->ReleaseStringUTFChars(name, className);

            std::cout << classNameStr << std::endl;

            classes.emplace(classNameStr, classesPtr[i]);
        }

        jvmti->Deallocate((unsigned char*)classesPtr);
    }

    jclass GetClass(std::string className)
    {
        if (classes.contains(className))
            return classes.at(className);

        return NULL;
    }

private:
    std::unordered_map<std::string, jclass> classes;
};

// Use make_unique with constructor parameters.
inline auto lc = std::make_unique<Lunar>(nullptr, nullptr);
