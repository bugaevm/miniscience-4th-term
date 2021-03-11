#include <set>
#include <gmsh.h>
#include <math.h>
#include <stdio.h>
#include <vector>

double lc = 1e-2;
double pi = 3.1415926535897932384626433832795;


int cnt_points = 1;
int cnt_lines = 1;
int cnt_surfs = 1;
int cnt_vols = 1;

int cnt_loops = 1;

int tor(double R, double r, double x, double y, double z) {
  gmsh::model::geo::addPoint(x, y, z, lc, cnt_points++);  // center
  int c_id = cnt_points - 1;
  
  
  
  int n = 8;
  
  for (int i = 0; i < n - 1; i++) {
    double c = cos(2 * pi * i / n);
    double s = sin(2 * pi * i / n);
    
    if (!i) {
      gmsh::model::geo::addPoint(x + R * c, y + R * s, z, lc, cnt_points++);
      gmsh::model::geo::addPoint(x + (R - r) * c, y + (R - r) * s, z, lc, cnt_points++);
      gmsh::model::geo::addPoint(x + (R + r) * c, y + (R + r) * s, z, lc, cnt_points++);
  
      gmsh::model::geo::addCircleArc(cnt_points - 2, cnt_points - 3, cnt_points - 1, cnt_lines++, s, -c, 0);  // 1
      gmsh::model::geo::addCircleArc(cnt_points - 2, cnt_points - 3, cnt_points - 1, cnt_lines++, -s, c, 0);  // 2
    }
    
    double c1 = cos(2 * pi * (i + 1) / n);
    double s1 = sin(2 * pi * (i + 1) / n);
    
       
    gmsh::model::geo::addPoint(x + R * c1, y + R * s1, z, lc, cnt_points++);
    gmsh::model::geo::addPoint(x + (R - r) * c1, y + (R - r) * s1, z, lc, cnt_points++);
    gmsh::model::geo::addPoint(x + (R + r) * c1, y + (R + r) * s1, z, lc, cnt_points++);
  
    gmsh::model::geo::addCircleArc(cnt_points - 2, cnt_points - 3, cnt_points - 1, cnt_lines++, s1, -c1, 0);  // 3
    gmsh::model::geo::addCircleArc(cnt_points - 2, cnt_points - 3, cnt_points - 1, cnt_lines++, -s1, c1, 0);  // 4
    
    
    gmsh::model::geo::addCircleArc(cnt_points - 5, c_id, cnt_points - 2, cnt_lines++, 0, 0, 1);  // 5
    gmsh::model::geo::addCircleArc(cnt_points - 4, c_id, cnt_points - 1, cnt_lines++, 0, 0, 1);  // 6
    
    
     if (!i) {
       gmsh::model::geo::addCurveLoop({cnt_lines - 6, cnt_lines - 1, -(cnt_lines - 4), -(cnt_lines - 2)}, cnt_loops++);
       gmsh::model::geo::addSurfaceFilling({cnt_loops - 1}, cnt_surfs++);
       
       gmsh::model::geo::addCurveLoop({cnt_lines - 5, cnt_lines - 1, -(cnt_lines - 3), -(cnt_lines - 2)}, cnt_loops++);
       gmsh::model::geo::addSurfaceFilling({cnt_loops - 1}, cnt_surfs++);
     }
     
     else {
       gmsh::model::geo::addCurveLoop({cnt_lines - 8, cnt_lines - 1, -(cnt_lines - 4), -(cnt_lines - 2)}, cnt_loops++);
       gmsh::model::geo::addSurfaceFilling({cnt_loops - 1}, cnt_surfs++);
       
       gmsh::model::geo::addCurveLoop({cnt_lines - 7, cnt_lines - 1, -(cnt_lines - 3), -(cnt_lines - 2)}, cnt_loops++);
       gmsh::model::geo::addSurfaceFilling({cnt_loops - 1}, cnt_surfs++);
       
       
     }
    
    // gmsh::model::geo::addCurveLoop({1, 6, -3, -5}, cnt_loops++);
    
    
    
     //break;
  }
  
  gmsh::model::geo::addCircleArc(cnt_points - 2, c_id, cnt_points - 3 * n + 1, cnt_lines++, 0, 0, 1);
  gmsh::model::geo::addCircleArc(cnt_points - 1, c_id, cnt_points - 3 * n + 2, cnt_lines++, 0, 0, 1);
  
  
  
  gmsh::model::geo::addCurveLoop({cnt_lines - 6, cnt_lines - 1, -(cnt_lines - 4 * n), -(cnt_lines - 2)}, cnt_loops++);
  gmsh::model::geo::addSurfaceFilling({cnt_loops - 1}, cnt_surfs++);
  
  gmsh::model::geo::addCurveLoop({cnt_lines - 5, cnt_lines - 1, -(cnt_lines - 4 * n + 1), -(cnt_lines - 2)}, cnt_loops++);
  gmsh::model::geo::addSurfaceFilling({cnt_loops - 1}, cnt_surfs++);
  
  
  std::vector<int> surs;
  
  for (int i = cnt_surfs - 2 * n; i < cnt_surfs; i++) {
    surs.push_back(i);
  }
  
  gmsh::model::geo::addSurfaceLoop(surs, cnt_loops++);
  
  
  return cnt_loops - 1;
}

int main() {
  gmsh::initialize();

  gmsh::model::add("t2");


  // gmsh::model::geo::addPoint(0, 0, 0, lc, 1);
  // gmsh::model::geo::addPoint(.1, 0, 0, lc, 2);
  // gmsh::model::geo::addPoint(.1, .1, 0, lc, 3);
  // gmsh::model::geo::addPoint(0, .1, 0, lc, 4);

  // gmsh::model::geo::addPoint(0, 0, .1, lc, 5);
  // gmsh::model::geo::addPoint(.1, 0, .1, lc, 6);
  // gmsh::model::geo::addPoint(.1, .1, .1, lc, 7);
  // gmsh::model::geo::addPoint(0, .1, .1, lc, 8);



  // gmsh::model::geo::addLine(1, 2, 1);
  // gmsh::model::geo::addLine(2, 3, 2);
  // gmsh::model::geo::addLine(3, 4, 3);
  // gmsh::model::geo::addLine(4, 1, 4);

  // gmsh::model::geo::addLine(5, 6, 5);
  // gmsh::model::geo::addLine(6, 7, 6);
  // gmsh::model::geo::addLine(7, 8, 7);
  // gmsh::model::geo::addLine(8, 5, 8);

  // for (int i = 0; i < 4; i++)
  //   gmsh::model::geo::addLine(i + 1, i + 5, i + 9);


  // gmsh::model::geo::addCurveLoop({1, 2, 3, 4}, 1);
  // gmsh::model::geo::addPlaneSurface({1}, 1);

  // gmsh::model::geo::addCurveLoop({5, 6, 7, 8}, 2);
  // gmsh::model::geo::addPlaneSurface({2}, 2);

  // gmsh::model::geo::addCurveLoop({1, 10, -5, -9}, 3);
  // gmsh::model::geo::addPlaneSurface({3}, 3);

  // gmsh::model::geo::addCurveLoop({2, 11, -6, -10}, 4);
  // gmsh::model::geo::addPlaneSurface({4}, 4);

  // gmsh::model::geo::addCurveLoop({3, 12, -7, -11}, 5);
  // gmsh::model::geo::addPlaneSurface({5}, 5);

  // gmsh::model::geo::addCurveLoop({4, 9, -8, -12}, 6);
  // gmsh::model::geo::addPlaneSurface({6}, 6);

  // gmsh::model::geo::addSurfaceLoop({1, 2, 3, 4, 5, 6}, 1);
  // gmsh::model::geo::addVolume({1});
  
  // gmsh::model::geo::addPoint(0, 0, -0.1, lc, 1);
  // gmsh::model::geo::addPoint(0.1, 0, -0.1, lc, 2);
  // gmsh::model::geo::addPoint(-0.1, 0, -0.1, lc, 3);
  
  // gmsh::model::geo::addCircleArc(2, 1, 3, 1);
  // gmsh::model::geo::addCircleArc(3, 1, 2, 2);
  
  // gmsh::model::geo::addCurveLoop({1, 2}, 1);


  // gmsh::model::geo::addPoint(0, 0, 0.1, lc, 4);
  // gmsh::model::geo::addPoint(0.1, 0, 0.1, lc, 5);
  // gmsh::model::geo::addPoint(-0.1, 0, 0.1, lc, 6);
  
  // gmsh::model::geo::addCircleArc(5, 4, 6, 3);
  // gmsh::model::geo::addCircleArc(6, 4, 5, 4);
  
  // gmsh::model::geo::addCurveLoop({3, 4}, 2);
  
  
  
  // gmsh::model::geo::addPlaneSurface({1}, 1);
  // gmsh::model::geo::addPlaneSurface({2}, 2);
  
  // gmsh::model::geo::addLine(3, 6, 5);
  // gmsh::model::geo::addLine(2, 5, 6);
  
  
  // gmsh::model::geo::addCurveLoop({1, 5, -3, -6}, 3);
  // gmsh::model::geo::addSurfaceFilling({3}, 3);
  
  
  // gmsh::model::geo::addCurveLoop({2, 6, -4, -5}, 4);
  // gmsh::model::geo::addSurfaceFilling({4}, 4);
  
  
  // double R, r, x, y, z;
  
  // x = 0;
  // y = 0;
  // z = 0;
  
  // R = 0.1;
  // r = 0.05;
  
  // gmsh::model::geo::addPoint(x, y, z, lc, cnt_points++);  // center
  // int c_id = cnt_points - 1;
  
  
  
  // int n = 8;
  
  // for (int i = 0; i < n - 1; i++) {
  //   double c = cos(2 * pi * i / n);
  //   double s = sin(2 * pi * i / n);
    
  //   if (!i) {
  //     gmsh::model::geo::addPoint(x + R * c, y + R * s, z, lc, cnt_points++);
  //     gmsh::model::geo::addPoint(x + (R - r) * c, y + (R - r) * s, z, lc, cnt_points++);
  //     gmsh::model::geo::addPoint(x + (R + r) * c, y + (R + r) * s, z, lc, cnt_points++);
  
  //     gmsh::model::geo::addCircleArc(cnt_points - 2, cnt_points - 3, cnt_points - 1, cnt_lines++, s, -c, 0);  // 1
  //     gmsh::model::geo::addCircleArc(cnt_points - 2, cnt_points - 3, cnt_points - 1, cnt_lines++, -s, c, 0);  // 2
  //   }
    
  //   double c1 = cos(2 * pi * (i + 1) / n);
  //   double s1 = sin(2 * pi * (i + 1) / n);
    
       
  //   gmsh::model::geo::addPoint(x + R * c1, y + R * s1, z, lc, cnt_points++);
  //   gmsh::model::geo::addPoint(x + (R - r) * c1, y + (R - r) * s1, z, lc, cnt_points++);
  //   gmsh::model::geo::addPoint(x + (R + r) * c1, y + (R + r) * s1, z, lc, cnt_points++);
  
  //   gmsh::model::geo::addCircleArc(cnt_points - 2, cnt_points - 3, cnt_points - 1, cnt_lines++, s1, -c1, 0);  // 3
  //   gmsh::model::geo::addCircleArc(cnt_points - 2, cnt_points - 3, cnt_points - 1, cnt_lines++, -s1, c1, 0);  // 4
    
    
  //   gmsh::model::geo::addCircleArc(cnt_points - 5, c_id, cnt_points - 2, cnt_lines++, 0, 0, 1);  // 5
  //   gmsh::model::geo::addCircleArc(cnt_points - 4, c_id, cnt_points - 1, cnt_lines++, 0, 0, 1);  // 6
    
    
  //    if (!i) {
  //      gmsh::model::geo::addCurveLoop({cnt_lines - 6, cnt_lines - 1, -(cnt_lines - 4), -(cnt_lines - 2)}, cnt_loops++);
  //      gmsh::model::geo::addSurfaceFilling({cnt_loops - 1}, cnt_surfs++);
       
  //      gmsh::model::geo::addCurveLoop({cnt_lines - 5, cnt_lines - 1, -(cnt_lines - 3), -(cnt_lines - 2)}, cnt_loops++);
  //      gmsh::model::geo::addSurfaceFilling({cnt_loops - 1}, cnt_surfs++);
  //    }
     
  //    else {
  //      gmsh::model::geo::addCurveLoop({cnt_lines - 8, cnt_lines - 1, -(cnt_lines - 4), -(cnt_lines - 2)}, cnt_loops++);
  //      gmsh::model::geo::addSurfaceFilling({cnt_loops - 1}, cnt_surfs++);
       
  //      gmsh::model::geo::addCurveLoop({cnt_lines - 7, cnt_lines - 1, -(cnt_lines - 3), -(cnt_lines - 2)}, cnt_loops++);
  //      gmsh::model::geo::addSurfaceFilling({cnt_loops - 1}, cnt_surfs++);
       
       
  //    }
    
    // gmsh::model::geo::addCurveLoop({1, 6, -3, -5}, cnt_loops++);
    
    
    
     //break;
  // }
  
  // gmsh::model::geo::addCircleArc(cnt_points - 2, c_id, cnt_points - 3 * n + 1, cnt_lines++, 0, 0, 1);
  // gmsh::model::geo::addCircleArc(cnt_points - 1, c_id, cnt_points - 3 * n + 2, cnt_lines++, 0, 0, 1);
  
  
  
  // gmsh::model::geo::addCurveLoop({cnt_lines - 6, cnt_lines - 1, -(cnt_lines - 4 * n), -(cnt_lines - 2)}, cnt_loops++);
  // gmsh::model::geo::addSurfaceFilling({cnt_loops - 1}, cnt_surfs++);
  
  // gmsh::model::geo::addCurveLoop({cnt_lines - 5, cnt_lines - 1, -(cnt_lines - 4 * n + 1), -(cnt_lines - 2)}, cnt_loops++);
  // gmsh::model::geo::addSurfaceFilling({cnt_loops - 1}, cnt_surfs++);
  
  
  // std::vector<int> surs;
  
  
  // for (int i = cnt_surfs - 2 * n; i < cnt_surfs; i++) {
  //   surs.push_back(i);
  // }
  

  
  // for (auto el : surs) {
  //   printf("%d ", el);
  // }
  // printf("\n");
  
  
  // gmsh::model::geo::addSurfaceLoop(surs, cnt_loops++);
  
  
  // int t1 = cnt_loops - 1;
  
  
  
  int t1 = tor(0.2, 0.07, 0, 0, 0);
  // printf("%d\n", t1);
  int t3 = tor(0.2, 0.05, 0, 0, 0);
  //printf("%d\n", t3);  
  gmsh::model::geo::addVolume({t1, -t3}, cnt_vols++);
  //printf("%d\n", t3);
  
  // printf("%f\n", sin(30 * pi / 180));
  



  gmsh::model::geo::synchronize();

  gmsh::model::mesh::generate(3);

  gmsh::write("t2.msh");

  gmsh::fltk::run();

  gmsh::finalize();

  return 0;
}

