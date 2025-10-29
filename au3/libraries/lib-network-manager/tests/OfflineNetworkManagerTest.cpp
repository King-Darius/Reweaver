#include <catch2/catch.hpp>

#include "NetworkManager.h"
#include "Request.h"

using namespace audacity::network_manager;

TEST_CASE("Network manager stub reports offline state", "[network][offline]")
{
    const Request request{"https://example.invalid/resource"};
    auto response = NetworkManager::GetInstance().doGet(request);

    bool callbackCalled = false;
    response->setRequestFinishedCallback([&](IResponse*) { callbackCalled = true; });

    REQUIRE(callbackCalled);
    REQUIRE(response->isFinished());
    REQUIRE(response->getError() != NetworkError::NoError);
    REQUIRE(response->getBytesAvailable() == 0);

    const auto errorString = response->getErrorString();
    REQUIRE(errorString.find("Reweaver") != std::string::npos);
}
