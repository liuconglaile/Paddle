/* Copyright (c) 2018 PaddlePaddle Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License. */

#include "paddle/fluid/framework/op_version_registry.h"
#include "paddle/fluid/operators/arg_min_max_op_base.h"

REGISTER_OPERATOR(
    arg_min, paddle::operators::ArgMinMaxOp, paddle::operators::ArgMinOpMaker,
    paddle::framework::EmptyGradOpMaker<paddle::framework::OpDesc>,
    paddle::framework::EmptyGradOpMaker<paddle::imperative::OpBase>);

REGISTER_OP_CPU_KERNEL(
    arg_min,
    paddle::operators::ArgMinKernel<paddle::platform::CPUDeviceContext, float>,
    paddle::operators::ArgMinKernel<paddle::platform::CPUDeviceContext, double>,
    paddle::operators::ArgMinKernel<paddle::platform::CPUDeviceContext,
                                    int64_t>,
    paddle::operators::ArgMinKernel<paddle::platform::CPUDeviceContext,
                                    int32_t>,
    paddle::operators::ArgMinKernel<paddle::platform::CPUDeviceContext,
                                    int16_t>,
    paddle::operators::ArgMinKernel<paddle::platform::CPUDeviceContext,
                                    uint8_t>);
REGISTER_OP_VERSION(arg_min)
    .AddCheckpoint(
        R"ROC(
              Upgrade argmin add a new attribute [flatten] and modify the attribute of dtype)ROC",
        paddle::framework::compatible::OpVersionDesc()
            .NewAttr("flatten",
                     "In order to compute the argmin over the flattened array "
                     "when the "
                     "argument `axis` in python API is None.",
                     false)
            .ModifyAttr(
                "dtype",
                "change the default value of dtype, the older version "
                "is -1, means return the int64 indices."
                "The new version is 3, return the int64 indices directly."
                "And supporting the dtype of -1 in new version.",
                3));
