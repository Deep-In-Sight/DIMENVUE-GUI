#include <context.hpp>
#include <mapVisualizer.hpp>

using namespace dimenvue::backend;

int main()
{
    auto &context = Context::getInstance();
    auto mapVisualizer = context.getMapVisualizer();
    mapVisualizer->zoomIn();

    return 0;
}