/**
 *  Copyright (C) 2023 WeDPR.
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
 * @file GatewayClient.h
 * @author: yujiechen
 * @date 2024-09-02
 */
#pragma once
#include "GrpcClient.h"
#include "ppc-framework/gateway/IGateway.h"

namespace ppc::protocol
{
class GatewayClient : public ppc::gateway::IGateway, public GrpcClient
{
public:
    using Ptr = std::shared_ptr<GatewayClient>;
    GatewayClient(std::shared_ptr<grpc::Channel> channel)
      : GrpcClient(std::move(channel)), m_stub(ppc::proto::Gateway::NewStub(m_channel))
    {}

    ~GatewayClient() override = default;


    void start() override {}
    void stop() override {}

    /**
     * @brief send message to gateway
     *
     * @param routeType the route type
     * @param topic  the topic
     * @param dstInst the dst agency(must set when 'route by agency' and 'route by
     * component')
     * @param dstNodeID  the dst nodeID(must set when 'route by nodeID')
     * @param componentType the componentType(must set when 'route by component')
     * @param payload the payload to send
     * @param seq the message seq
     * @param timeout timeout
     * @param callback callback
     */
    void asyncSendMessage(ppc::protocol::RouteType routeType,
        ppc::protocol::MessageOptionalHeader::Ptr const& routeInfo, bcos::bytes&& payload,
        long timeout, ppc::protocol::ReceiveMsgFunc callback) override;

    void asyncSendbroadcastMessage(ppc::protocol::RouteType routeType,
        ppc::protocol::MessageOptionalHeader::Ptr const& routeInfo, bcos::bytes&& payload) override
    {}
    bcos::Error::Ptr registerNodeInfo(ppc::protocol::INodeInfo::Ptr const& nodeInfo) override;
    bcos::Error::Ptr unRegisterNodeInfo(bcos::bytesConstRef nodeID) override;
    bcos::Error::Ptr registerTopic(bcos::bytesConstRef nodeID, std::string const& topic) override;
    bcos::Error::Ptr unRegisterTopic(bcos::bytesConstRef nodeID, std::string const& topic) override;

private:
    std::unique_ptr<ppc::proto::Gateway::Stub> m_stub;
};
}  // namespace ppc::protocol