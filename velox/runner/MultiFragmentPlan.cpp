/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "velox/runner/MultiFragmentPlan.h"

namespace facebook::velox::runner {

std::string MultiFragmentPlan::toString(bool detailed) const {
  std::stringstream out;
  for (auto i = 0; i < fragments_.size(); ++i) {
    out << fmt::format(
        "Fragment {}: {} numWorkers={}:\n",
        i,
        fragments_[i].taskPrefix,
        fragments_[i].width);
    out << fragments_[i].fragment.planNode->toString(detailed, true)
        << std::endl;
    if (!fragments_[i].inputStages.empty()) {
      out << "Inputs: ";
      for (auto& input : fragments_[i].inputStages) {
        out << fmt::format(
            " {} <- {} ", input.consumerNodeId, input.producerTaskPrefix);
      }
      out << std::endl;
    }
  }
  return out.str();
}

} // namespace facebook::velox::runner
