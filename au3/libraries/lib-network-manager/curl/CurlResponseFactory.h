/*!********************************************************************

 Audacity: A Digital Audio Editor

 @file CurlResponseFactory.h
 @brief Declare an offline implementation of IResponseFactory.

 **********************************************************************/

#pragma once

#include <memory>

#include "../IResponseFactory.h"

namespace audacity {
namespace network_manager {

class CurlResponseFactory final : public IResponseFactory
{
public:
    CurlResponseFactory() = default;
    ~CurlResponseFactory() override = default;

    void setProxy(const std::string& proxy) override;

    ResponsePtr performRequest(RequestVerb verb, const Request& request) override;
    ResponsePtr performRequest(
        RequestVerb verb, const Request& request, RequestPayloadStreamPtr payloadStream) override;
    ResponsePtr performRequest(
        RequestVerb verb, const Request& request, std::unique_ptr<MultipartData> form) override;

    void terminate() override;
};

} // namespace network_manager
} // namespace audacity
