/*
 * murmur3.cpp
 * Copyright (C) 2015 Kurten Chan <chinkurten@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#include <node.h>
#include <node_buffer.h>

#include <string.h>
#include <stdlib.h>

#include "MurmurHash3.h"

using namespace node;

namespace {

    using v8::Exception;
    using v8::FunctionCallbackInfo;
    using v8::Isolate;
    using v8::Local;
    using v8::Number;
    using v8::Object;
    using v8::String;
    using v8::Value;
    using v8::Boolean;
    using v8::Array;

    void hash(const FunctionCallbackInfo<Value>& args) {
        Isolate* isolate = args.GetIsolate();

        if (args.Length() < 2) {
            isolate->ThrowException(Exception::TypeError(
                String::NewFromUtf8(isolate, "Wrong number of arguments")));
            return;
        }

        if (!args[0]->IsString() || !args[1]->IsNumber()) {
            isolate->ThrowException(Exception::TypeError(
                String::NewFromUtf8(isolate, "Wrong arguments")));
            return;
        }

        int32_t result[1];

        String::Utf8Value key(args[0]->ToString());
        uint32_t seed = args[1]->Int32Value();

        MurmurHash3_x86_32(*key, strlen(*key), seed, result);

        Local<Number> num = Number::New(isolate, result[0]);
        args.GetReturnValue().Set(num);
    }
    
    void hash64(const FunctionCallbackInfo<Value>& args) {
        Isolate* isolate = args.GetIsolate();
        
        if (args.Length() < 3) {
            isolate->ThrowException(Exception::TypeError(
                String::NewFromUtf8(isolate, "Wrong number of arguments")));
            return;
        }

        if (!args[0]->IsString() || !args[1]->IsNumber() ||!args[2]->IsBoolean()) {
            isolate->ThrowException(Exception::TypeError(
                String::NewFromUtf8(isolate, "Wrong arguments")));
            return;
        }

        String::Utf8Value key(args[0]->ToString());
        uint32_t seed = args[1]->Int32Value();
        bool x64arch = args[2]->BooleanValue();

        int64_t result[2];
        
        if (x64arch) {
            MurmurHash3_x64_128(*key, strlen(*key), seed, result);
        } else {
            MurmurHash3_x86_128(*key, strlen(*key), seed, result);
        }

        Local<Array> nums = Array::New(isolate);
        nums->Set(0, Number::New(isolate, result[0]));
        nums->Set(1, Number::New(isolate, result[1]));
        args.GetReturnValue().Set(nums);
    }

    void hash_bytes(const FunctionCallbackInfo<Value>& args) {
        Isolate* isolate = args.GetIsolate();
        
        if (args.Length() < 3) {
            isolate->ThrowException(Exception::TypeError(
                String::NewFromUtf8(isolate, "Wrong number of arguments")));
            return;
        }

        if (!args[0]->IsString() || !args[1]->IsNumber() ||!args[2]->IsBoolean()) {
            isolate->ThrowException(Exception::TypeError(
                String::NewFromUtf8(isolate, "Wrong arguments")));
            return;
        }

        String::Utf8Value key(args[0]->ToString());
        uint32_t seed = args[1]->Int32Value();
        bool x64arch = args[2]->BooleanValue();

        uint32_t result[4];
        if (x64arch) {
            MurmurHash3_x64_128(*key, strlen(*key), seed, result);
        } else {
            MurmurHash3_x86_128(*key, strlen(*key), seed, result);
        }

        char *bytes = static_cast<char*>(malloc(16));
        memcpy(bytes, result, 16);
        Local<Object> obj = Buffer::New(isolate, bytes, 16).ToLocalChecked();
        args.GetReturnValue().Set(obj);
    }

    void Init(Local<Object> exports) {
        NODE_SET_METHOD(exports, "hash", hash);
        NODE_SET_METHOD(exports, "hash64", hash64);
        NODE_SET_METHOD(exports, "hash_bytes", hash_bytes);
    }

    NODE_MODULE(murmur3, Init)
}


