/*!********************************************************************

 Audacity: A Digital Audio Editor

 @file CurlResponse.cpp
 @brief Define an offline implementation of IResponse.

 **********************************************************************/

#include "CurlResponse.h"

namespace audacity {
namespace network_manager {
namespace {
constexpr const char* kOfflineMessage = "Networking is disabled in Reweaver.";
}

CurlResponse::CurlResponse(RequestVerb verb, const Request& request) noexcept
    : mVerb(verb)
    , mRequest(request)
{
}

bool CurlResponse::isFinished() const noexcept
{
    return true;
}

unsigned CurlResponse::getHTTPCode() const noexcept
{
    return 0;
}

NetworkError CurlResponse::getError() const noexcept
{
    return mAborted ? NetworkError::OperationCancelled : NetworkError::ConnectionFailed;
}

std::string CurlResponse::getErrorString() const
{
    return kOfflineMessage;
}

bool CurlResponse::headersReceived() const noexcept
{
    return false;
}

bool CurlResponse::hasHeader(const std::string&) const noexcept
{
    return false;
}

std::string CurlResponse::getHeader(const std::string&) const
{
    return {};
}

const HeadersList& CurlResponse::getHeaders() const noexcept
{
    static HeadersList empty;
    return empty;
}

const CookiesList& CurlResponse::getCookies() const noexcept
{
    static CookiesList empty;
    return empty;
}

const Request& CurlResponse::getRequest() const noexcept
{
    return mRequest;
}

std::string CurlResponse::getURL() const
{
    return mRequest.getURL();
}

void CurlResponse::abort() noexcept
{
    mAborted = true;
}

void CurlResponse::setOnDataReceivedCallback(RequestCallback)
{
    // Offline stub; no data will be delivered.
}

void CurlResponse::setRequestFinishedCallback(RequestCallback callback)
{
    if (callback) {
        callback(this);
    }
}

void CurlResponse::setDownloadProgressCallback(ProgressCallback)
{
}

void CurlResponse::setUploadProgressCallback(ProgressCallback)
{
}

uint64_t CurlResponse::getBytesAvailable() const noexcept
{
    return 0;
}

uint64_t CurlResponse::readData(void*, uint64_t)
{
    return 0;
}

} // namespace network_manager
} // namespace audacity
