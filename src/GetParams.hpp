/**
 * @brief Helper to access GET parameters
 */
#pragma once

#include <boost/beast/http.hpp>
#include <boost/url.hpp>
#include <boost/url/encoding_opts.hpp>
#include <boost/url/decode_view.hpp>
#include <optional>
#include <string_view>

class GetParams {
    using Request = boost::beast::http::request<boost::beast::http::string_body>;

public:
    explicit GetParams(Request const &req)
            : target(req.target()), url(target), params(url.params()) {
    }

    std::optional<std::string> get(std::string_view name) const {
        auto it = params.find(name);
        if (it == params.end())
            return std::nullopt;

        const std::string value = (*it).value;
        auto dv = boost::urls::decode_view(value);
        return std::string(dv.begin(), dv.end()); // copy
    }


private:
    std::string target;
    boost::urls::url_view url;
    boost::urls::params_view params;
};
