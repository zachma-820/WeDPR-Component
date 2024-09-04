/*
 *  Copyright (C) 2022 WeDPR.
 *  SPDX-License-Identifier: Apache-2.0
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 * @file Common.h
 * @author: yujiechen
 * @date 2022-11-2
 */
#pragma once
#include "ppc-framework/Common.h"
#include <bcos-utilities/Log.h>
#include <memory>

namespace ppc::crypto
{
DERIVE_PPC_EXCEPTION(HashException);
DERIVE_PPC_EXCEPTION(SymCryptoException);
DERIVE_PPC_EXCEPTION(OreException);

DERIVE_PPC_EXCEPTION(UnsupportedHashType);
DERIVE_PPC_EXCEPTION(BitVectorException);
DERIVE_PPC_EXCEPTION(FastOreException);
}  // namespace ppc::crypto