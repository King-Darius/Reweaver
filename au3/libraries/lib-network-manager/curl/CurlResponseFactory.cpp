/*!********************************************************************

 Audacity: A Digital Audio Editor

 @file CurlResponseFactory.cpp
 @brief Define an offline implementation of IResponseFactory.

 **********************************************************************/

#include "CurlResponseFactory.h"

#include "CurlResponse.h"
#include "MultipartData.h"
#include "RequestPayload.h"

namespace audacity {
namespace network_manager {

void CurlResponseFactory::setProxy(const std::string&)
{
    // Networking is disabled; proxies are ignored.
}

ResponsePtr CurlResponseFactory::performRequest(RequestVerb verb, const Request& request)
{
    return performRequest(verb, request, RequestPayloadStreamPtr {});
}

ResponsePtr CurlResponseFactory::performRequest(
    RequestVerb verb, const Request& request, RequestPayloadStreamPtr /*payloadStream*/)
{
    return std::make_shared<CurlResponse>(verb, request);
}

ResponsePtr CurlResponseFactory::performRequest(
    RequestVerb verb, const Request& request, std::unique_ptr<MultipartData> /*form*/)
{
    return std::make_shared<CurlResponse>(verb, request);
}

void CurlResponseFactory::terminate()
{
    // Nothing to clean up in the offline stub.
}

} // namespace network_manager
} // namespace audacity
