/*!********************************************************************

 Audacity: A Digital Audio Editor

 @file CurlResponse.h
 @brief Declare an offline implementation of IResponse.

 **********************************************************************/

#pragma once

#include <string>

#include "../IResponse.h"
#include "../HeadersList.h"
#include "../CookiesList.h"
#include "../Request.h"

namespace audacity {
namespace network_manager {

class CurlResponse final : public IResponse
{
public:
    CurlResponse(RequestVerb verb, const Request& request) noexcept;

    bool isFinished() const noexcept override;
    unsigned getHTTPCode() const noexcept override;

    NetworkError getError() const noexcept override;
    std::string getErrorString() const override;

    bool headersReceived() const noexcept override;

    bool hasHeader(const std::string& headerName) const noexcept override;
    std::string getHeader(const std::string& headerName) const override;

    const HeadersList& getHeaders() const noexcept override;
    const CookiesList& getCookies() const noexcept override;

    const Request& getRequest() const noexcept override;

    std::string getURL() const override;

    void abort() noexcept override;

    void setOnDataReceivedCallback(RequestCallback callback) override;

    void setRequestFinishedCallback(RequestCallback callback) override;

    void setDownloadProgressCallback(ProgressCallback callback) override;
    void setUploadProgressCallback(ProgressCallback callback) override;

    uint64_t getBytesAvailable() const noexcept override;
    uint64_t readData(void* buffer, uint64_t maxBytesCount) override;

private:
    RequestVerb mVerb;
    Request mRequest;
    bool mAborted { false };
};

} // namespace network_manager
} // namespace audacity
