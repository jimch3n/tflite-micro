/* Copyright 2020 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/
#ifndef TENSORFLOW_LITE_MICRO_DMX1A_DEBUG_LOG_CALLBACK_H_
#define TENSORFLOW_LITE_MICRO_DMX1A_DEBUG_LOG_CALLBACK_H_

// The application layer must implement and register a callback before calling
// the network in a way similar to
//
//    void debug_log_printf(const char* s)
//    {
//        printf(s);
//    }
//
//    int main(void)
//    {
//        // Register callback for printing debug log
//        RegisterDebugLogCallback(debug_log_printf);
//
//        // now call the network
//        TfLiteStatus invoke_status = interpreter->Invoke();
//    }

typedef int (*DebugLogCallback)(unsigned char pluginInstanceID,
                                const char *pBuf);

// Registers and application-specific callback for debug logging. It must be
// called before the first call to DebugLog().
void RegisterDebugLogCallback(DebugLogCallback callback,
                              unsigned char pluginInstanceID);

int debug_log_printf(unsigned char pluginInstId, const char *pBuf);

#endif  // TENSORFLOW_LITE_MICRO_DMX1A_DEBUG_LOG_CALLBACK_H_
