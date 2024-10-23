#include <memory>

namespace dimenvue
{
    namespace backend
    {
        class ScanViewInterface;

        enum ProjectionMode
        {
            PERSPECTIVE,
            ORTHOGRAPHIC
        };

        class MapVisualizerInterface
        {
        public:
            MapVisualizerInterface();
            ~MapVisualizerInterface();

            void setScanView(const std::shared_ptr<ScanViewInterface> &scanView);
            void setMeasurementMode(bool enable);
            bool isMeasurementModeEnabled();
            void setProjectionMode(ProjectionMode mode);
            ProjectionMode getProjectionMode();
            void zoomIn();
            void zoomOut();

        private:
            struct Impl;
            std::unique_ptr<Impl> _impl;
        };
    } // namespace backend
} // namespace dimenvue