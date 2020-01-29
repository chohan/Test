// g++ -g -w -o tp ThreadPool.cpp --std=c++17 -lpthread && ./tp

#include <vector>
#include <queue>
#include <functional>
#include <condition_variable>
#include <thread>
#include <future>

//namespace linx {

class ThreadPool final {
public:
    using Task = std::function<void()>;

private:    
    std::vector<std::thread> _threads;
    std::queue<Task>         _tasks;

    std::condition_variable  _con_var;
    std::mutex               _mutex;
    bool                     _stopping = false;    

public:
    explicit ThreadPool( std::size_t numThreads ) {
        start( numThreads );
    }    

    ~ThreadPool() {
        stop();
    }

    ThreadPool( const ThreadPool& c ) = delete;
    ThreadPool& operator=( const ThreadPool& c ) = delete;

    template<class T>
    auto enqueue( T task )->std::future<decltype(task())> {
        auto wrapper = std::make_shared<std::packaged_task<decltype(task()) ()>>( std::move( task ) );

        {
            std::unique_lock<std::mutex> lock( _mutex );
            _tasks.emplace( [=] {
                (*wrapper)();
            } );
        }

        _con_var.notify_one();
        return wrapper->get_future();
    }

private:
    void start( std::size_t numThreads ) {
        for( auto i = 0u; i < numThreads; ++i ) {
            _threads.emplace_back( [=] {
                while( true ) {
                    Task task;

                    {
                        std::unique_lock<std::mutex> lock{ _mutex };
                        _con_var.wait( lock, [=] { return _stopping || !_tasks.empty(); } );

                        if( _stopping && _tasks.empty() )
                            break;

                        task = std::move( _tasks.front() );
                        _tasks.pop();
                    }

                    task();
                }
            } );
        }
    }

    void stop() noexcept {
        {
            std::unique_lock<std::mutex> lock{ _mutex };
            _stopping = true;
        }

        _con_var.notify_all();

        for( auto& thread : _threads )
            thread.join();

    }
};

//} // namespace linx


#include <iostream>
#include <sstream>

int main() {
    {
        ThreadPool pool(4); // 4 threads

        auto f1 = pool.enqueue( [] {return 2;} );

        auto f2 = pool.enqueue( [] {return 4;} );

        auto a = f1.get();
        auto b = f2.get();

        auto f3 = pool.enqueue( [&] {return a + b;} );

        auto f4 = pool.enqueue( [&] {return a * b;} );

        std::cout << "f1 = " << a << '\n'
                  << "f2 = " << b << '\n'
                  << "f3 = " << f3.get() << '\n'
                  << "f4 = " << f4.get() << '\n';
    }                 

    std::cout << "\nPress any key and enter to quit.\n";
    std::cin.get();
    return 0;
}
