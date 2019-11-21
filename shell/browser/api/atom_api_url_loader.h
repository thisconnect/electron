// Copyright (c) 2019 Slack Technologies, Inc.
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef SHELL_BROWSER_API_ATOM_API_URL_LOADER_H_
#define SHELL_BROWSER_API_ATOM_API_URL_LOADER_H_

#include "net/base/auth.h"
#include "services/network/public/cpp/simple_url_loader_stream_consumer.h"
#include "services/network/public/mojom/network_context.mojom.h"
#include "services/network/public/mojom/url_loader_factory.mojom-forward.h"
#include "services/network/public/mojom/url_response_head.mojom.h"
#include "shell/common/gin_helper/event_emitter.h"
#include "url/gurl.h"
#include "v8/include/v8.h"

namespace gin {
class Arguments;
}

namespace network {
class SimpleURLLoader;
struct ResourceRequest;
}  // namespace network

namespace electron {

namespace api {

/** Wraps a SimpleURLLoader to make it usable from JavaScript */
class SimpleURLLoaderWrapper
    : public gin_helper::EventEmitter<SimpleURLLoaderWrapper>,
      public network::SimpleURLLoaderStreamConsumer {
 public:
  ~SimpleURLLoaderWrapper() override;
  static mate::WrappableBase* New(gin::Arguments* args);

  static void BuildPrototype(v8::Isolate* isolate,
                             v8::Local<v8::FunctionTemplate> prototype);

  static SimpleURLLoaderWrapper* FromID(uint32_t id);

  void OnAuthRequired(
      const GURL& url,
      bool first_auth_attempt,
      net::AuthChallengeInfo auth_info,
      network::mojom::URLResponseHeadPtr head,
      mojo::PendingRemote<network::mojom::AuthChallengeResponder>
          auth_challenge_responder);

  void Cancel();

 private:
  SimpleURLLoaderWrapper(std::unique_ptr<network::ResourceRequest> loader,
                         network::mojom::URLLoaderFactory* url_loader_factory);

  // SimpleURLLoaderStreamConsumer:
  void OnDataReceived(base::StringPiece string_piece,
                      base::OnceClosure resume) override;
  void OnComplete(bool success) override;
  void OnRetry(base::OnceClosure start_retry) override;

  // SimpleURLLoader callbacks
  void OnResponseStarted(const GURL& final_url,
                         const network::mojom::URLResponseHead& response_head);

  void Start();

  uint32_t id_;
  std::unique_ptr<network::SimpleURLLoader> loader_;
  v8::Global<v8::Value> pinned_wrapper_;
};

}  // namespace api

}  // namespace electron

#endif  // SHELL_BROWSER_API_ATOM_API_URL_LOADER_H_