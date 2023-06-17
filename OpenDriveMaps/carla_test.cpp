#include "Lane.h"
#include "LaneSection.h"
#include "Math.hpp"
#include "Mesh.h"
#include "OpenDriveMap.h"
#include "Road.h"

#include <iostream>

const double eps = 1;


int main(int argc, char** argv)
{
    if(argc < 2)
    {
        std::cout << "Too less arguments, provide a path for opedrive map file" << std::endl;
    }
    std::cout << "Town Map : " << argv[1] << std::endl;
    odr::OpenDriveMap odr_map(argv[1]);
    std::vector<odr::Vec3D> sidewalks;
    for(odr::Road road : odr_map.get_roads())
    {
        for(odr::LaneSection lanesection : road.get_lanesections())
        {
            for(odr::Lane lane : lanesection.get_lanes())
            {
                ///std::cout << lane.type << std::endl;
                if(lane.type == "sidewalk")
                {
                    odr::Mesh3D lane_mesh = road.get_lane_mesh(lane, eps);
                    sidewalks.insert(sidewalks.end(), lane_mesh.vertices.begin(), lane_mesh.vertices.end());
                }
            }
        }
    }
    std::cout << "Print 5 points....." << std::endl;
    for(odr::Vec3D points : sidewalks)
    {
        std::cout << "(" << points[0] << "," << points[1] << "," << points[2] << ")" << std::endl;
    }
    std::cout << "Total sidewalks points : " << sidewalks.size() << std::endl;

}