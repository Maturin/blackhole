#include <boost/lexical_cast.hpp>

#include <blackhole/handler.hpp>
#include <blackhole/root.hpp>

#include <thread>

using namespace blackhole;

int main(int, char** argv) {
    const auto thread_num = boost::lexical_cast<int>(argv[1]);
    const auto iterations = boost::lexical_cast<int>(argv[2]);

    root_logger_t logger({});

    std::vector<std::thread> threads;

    for (int tid = 0; tid < thread_num; ++tid) {
        threads.emplace_back([&] {
            for (int i = 0; i < iterations; ++i) {
                logger.log(0, "GET /porn.png HTTP/1.1");
            }
        });
    }

    bool allow = false;
    for (int i = 0; i < iterations; ++i) {
        allow = !allow;
        logger.filter([=](const record_t&) -> bool {
            return allow;
        });
    }

    for (auto& thread : threads) {
        thread.join();
    }
}
