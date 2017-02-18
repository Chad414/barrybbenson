#include <stdio.h>

#include "pathfinder.h"

#define USE_CPP_OUTPUT

#define WHEEL_RADIUS_METERS .47879

int main()
{
    int POINT_LENGTH = 2;

    Waypoint *points = (Waypoint*)malloc(sizeof(Waypoint) * POINT_LENGTH);

    Waypoint p1 = { 0, 0, d2r(90) };      		// Waypoint
    Waypoint p2 = { -1.49, 2.63, d2r(150) };             		// Waypoint
//    Waypoint p3 = { 8, 12*, d2r(90) };             		// Waypoint
//    Waypoint p4 = { 6, 2, d2r(-45) };             	// Waypoint
//    Waypoint p5 = { 8, 0, d2r(-90) };             	// Waypoint
    points[0] = p1;
    points[1] = p2;
//    points[2] = p3;
//    points[3] = p4;
//    points[4] = p5;
    
    puts("init");

    TrajectoryCandidate candidate;
    pathfinder_prepare(points, POINT_LENGTH, FIT_HERMITE_QUINTIC, PATHFINDER_SAMPLES_HIGH, 0.02, 3.351, 3.351*2, 3.351*4, &candidate); //numbers are interval in seconds, max velocity in units/second, max acceleration in units/second^2, and max jerk in units/seconds^3

    puts("prepared");

    int length = candidate.length;
    Segment *trajectory = malloc(length * sizeof(Segment));
    
    pathfinder_generate(&candidate, trajectory);
    
    puts("generated");

    Segment *leftTrajectory = (Segment*)malloc(sizeof(Segment) * length);
    Segment *rightTrajectory = (Segment*)malloc(sizeof(Segment) * length);
    
    double wheelbase_width = 0.6;

    pathfinder_modify_tank(trajectory, length, leftTrajectory, rightTrajectory, wheelbase_width);

    puts("modified");



    FILE *ptr_file;
    int i;
#ifdef USE_CPP_OUTPUT
    ptr_file =fopen("motionprofiles.cpp", "w");

    fprintf(ptr_file, "#include <motionprofiles.h>\n\n");
    fprintf(ptr_file, "std::vector<std::vector<double>> profileLeft() {\n return {\n");
#else
    ptr_file = fopen("output.csv", "w");
    fprintf(ptr_file, "LeftX, LeftY, RightX, RightY, Time, LeftVel, RightVel, Time, LeftAccel, RightAccel, Time, LeftJerk, RightJerk\n");
#endif
    for (i = 0; i < length; i++) {
    	Segment l = leftTrajectory[i];
    	Segment r = rightTrajectory[i];
#ifdef USE_CPP_OUTPUT
    	fprintf(ptr_file, "{%f, %f, %f}", l.position, l.velocity, l.dt);
    	if (i + 1 != length)
    		fprintf(ptr_file, ",");
    	fprintf(ptr_file, "\n");
#else
    	fprintf(ptr_file,"%f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f\n", l.x, l.y, r.x, r.y, (i*l.dt), l.velocity, r.velocity, (i*l.dt), l.acceleration, r.acceleration,(i*l.dt), l.jerk, r.jerk);
#endif
    }
#ifdef USE_CPP_OUTPUT
    fprintf(ptr_file, "};\n}\n\n\n");

    fprintf(ptr_file, "std::vector<std::vector<double>> profileRight() {\n return {\n");

    for (i = 0; i < length; i++)
    {
    	Segment r = rightTrajectory[i];
    	fprintf(ptr_file, "{%f, %f, %f}", r.position * WHEEL_RADIUS_METERS, r.velocity * WHEEL_RADIUS_METERS * 60, r.dt * 1000);
    	if (i + 1 != length)
    		fprintf(ptr_file, ",");
    	fprintf(ptr_file, "\n");
    }
    fprintf(ptr_file, "};\n}\n\n\n");
    fclose(ptr_file);

    ptr_file = fopen("motionprofiles.h", "w");
    fprintf(ptr_file, "#ifndef _motionprofiles_\n#define_motionprofiles_\nstd::vector<std::vector<double>> profileLeft()\nstd::vector<std::vector<double>> profileRight()\n#endif\n");
    fclose(ptr_file);
#endif

	ptr_file =fopen("left.csv", "w");
	fprintf(ptr_file, "Time,x Coord, yCoord, Distance, Velocity, Accel, Jerk, Heading\n");
    for (i = 0; i < length; i++) {
        Segment s = leftTrajectory[i];
        fprintf(ptr_file,"%f, %f, %f, %f, %f, %f, %f, %f\n", s.dt, s.x, s.y, s.position, s.velocity, s.acceleration, s.jerk, s.heading);
    }
	fclose(ptr_file);

	ptr_file =fopen("right.csv", "w");
	fprintf(ptr_file, "Time,x Coord, yCoord, Distance, Velocity, Accel, Jerk, Heading\n");
    for (i = 0; i < length; i++) {
        Segment s = rightTrajectory[i];
        fprintf(ptr_file,"%f, %f, %f, %f, %f, %f, %f, %f\n", s.dt, s.x, s.y, s.position, s.velocity, s.acceleration, s.jerk, s.heading);
    }
	fclose(ptr_file);


    free(trajectory);


    return 0;
}
