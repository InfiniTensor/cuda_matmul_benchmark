/*
 * Copyright (c) 2020, NVIDIA CORPORATION. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *  * Neither the name of NVIDIA CORPORATION nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <vector>

#include <cuda_runtime_api.h>
#include <cublasLt.h>

#include "sample_cublasLt_LtSgemmCustomFind.h"
#include "helpers.h"

int main()
{
    int M = 512;
    int N = 4096;
    int K = 4096;
    float alpha = 1.0f;
    float beta = 0.0f;
    int dtype = DTYPE_HALF;

    if (dtype == DTYPE_FLOAT)
    {
        TestBench<float> props(M, N, K, alpha, beta, 1024 * 1024 * 4);
        props.run([&props, dtype]
                  { LtSgemmCustomFind(props.ltHandle,
                                      CUBLAS_OP_N,
                                      CUBLAS_OP_N,
                                      props.m,
                                      props.n,
                                      props.k,
                                      &props.alpha,
                                      props.Adev,
                                      props.m,
                                      props.Bdev,
                                      props.k,
                                      &props.beta,
                                      props.Cdev,
                                      props.m,
                                      props.workspace,
                                      props.workspaceSize,
                                      dtype); });
    }
    else if (dtype == DTYPE_HALF)
    {
        TestBench<__half> props(M, N, K, __half(alpha), __half(beta), 1024 * 1024 * 4);
        props.run([&props, dtype]
                  { LtSgemmCustomFind(props.ltHandle,
                                      CUBLAS_OP_N,
                                      CUBLAS_OP_N,
                                      props.m,
                                      props.n,
                                      props.k,
                                      &props.alpha,
                                      props.Adev,
                                      props.m,
                                      props.Bdev,
                                      props.k,
                                      &props.beta,
                                      props.Cdev,
                                      props.m,
                                      props.workspace,
                                      props.workspaceSize,
                                      dtype); });
    }

    return 0;
}