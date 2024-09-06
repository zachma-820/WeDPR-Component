/*
 * Copyright 2017-2025  [webank-wedpr]
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except
 * in compliance with the License. You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software distributed under the License
 * is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express
 * or implied. See the License for the specific language governing permissions and limitations under
 * the License.
 *
 */

package com.webank.wedpr.sdk.jni.demo;

import com.webank.wedpr.sdk.jni.generated.*;
import com.webank.wedpr.sdk.jni.generated.Error;
import com.webank.wedpr.sdk.jni.transport.IMessage;
import com.webank.wedpr.sdk.jni.transport.TransportConfig;
import com.webank.wedpr.sdk.jni.transport.WeDPRTransport;
import com.webank.wedpr.sdk.jni.transport.handlers.MessageDispatcherCallback;
import com.webank.wedpr.sdk.jni.transport.impl.TransportImpl;
import com.webank.wedpr.sdk.jni.transport.model.TransportEndPoint;

public class TransportDemo {
    public static class MessageDispatcherCallbackImpl extends MessageDispatcherCallback {
        private final String nodeID;

        public MessageDispatcherCallbackImpl(String nodeID) {
            this.nodeID = nodeID;
        }

        @Override
        public void onMessage(IMessage message) {
            System.out.println(
                    "##### Node: "
                            + nodeID
                            + " receiveMessage, detail: "
                            + message.toString()
                            + ", ");
        }
    }

    public static class MessageErrorCallback extends ErrorCallback {
        private final String nodeID;

        public MessageErrorCallback(String nodeID) {
            this.nodeID = nodeID;
        }

        @Override
        public void onError(Error error) {
            System.out.println(
                    "##### Node: "
                            + nodeID
                            + " MessageErrorCallback, result: "
                            + error.errorMessage()
                            + ", code:"
                            + error.errorCode());
        }
    }

    public static void main(String[] args) throws Exception {
        String nodeID = "testNode";
        if (args.length > 1) {
            nodeID = args[0];
        }
        TransportConfig transportConfig = new TransportConfig(2, nodeID);
        String hostIp = "127.0.0.1";
        if (args.length > 2) {
            hostIp = args[1];
        }
        int listenPort = 9020;
        if (args.length > 3) {
            listenPort = Integer.valueOf(args[2]);
        }
        String listenIp = "0.0.0.0";
        TransportEndPoint endPoint = new TransportEndPoint(hostIp, listenIp, listenPort);
        transportConfig.setSelfEndPoint(endPoint);
        String grpcTarget = "ipv4:127.0.0.1:40600,127.0.0.1:40601";
        if (args.length > 4) {
            grpcTarget = args[3];
        }
        transportConfig.setGatewayTargets(grpcTarget);
        System.out.println("####### transportConfig: " + transportConfig.toString());
        // build the gatewayTarget
        WeDPRTransport transport = TransportImpl.build(transportConfig);

        System.out.println("####### before start the transport");
        transport.start();
        System.out.println("####### start the transport success");

        // send Message to the gateway
        String topic = "testTopic";
        transport.registerTopicHandler(topic, new MessageDispatcherCallbackImpl(nodeID));
        System.out.println("##### register topic success");
        String dstNode = "agency2Node";
        if (args.length > 5) {
            dstNode = args[5];
        }

        byte[] dstNodeBytes = dstNode.getBytes();
        // every 2s send a message
        Integer i = 0;
        while (true) {
            String payLoad = "testPayload" + i;
            transport.asyncSendMessageByNodeID(
                    topic,
                    dstNodeBytes,
                    payLoad.getBytes(),
                    0,
                    10000,
                    new MessageErrorCallback(nodeID),
                    null);
            i++;
            Thread.sleep(2000);
        }
    }
}