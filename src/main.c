#include <stdio.h>

#include "pathfinder.h"


int main()
{
    int POINT_LENGTH = 3;

    Waypoint *points = (Waypoint*)malloc(sizeof(Waypoint) * POINT_LENGTH);

    Waypoint p1 = { 0, 0, d2r(90) };      		// Waypoint
    Waypoint p2 = { 4, 10, d2r(45) };             		// Waypoint
    Waypoint p3 = { 8, 12, d2r(90) };             		// Waypoint
//    Waypoint p4 = { 6, 2, d2r(-45) };             	// Waypoint
//    Waypoint p5 = { 8, 0, d2r(-90) };             	// Waypoint
    points[0] = p1;
    points[1] = p2;
    points[2] = p3;
//    points[3] = p4;
//    points[4] = p5;
    
    puts("init");

    TrajectoryCandidate candidate;
    pathfinder_prepare(points, POINT_LENGTH, FIT_HERMITE_QUINTIC, PATHFINDER_SAMPLES_HIGH, 0.01, 15.0, 20, 15, &candidate);

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

    ptr_file =fopen("output.csv", "w");
    fprintf(ptr_file, "LeftX, LeftY, RightX, RightY, Time, LeftVel, RightVel, Time, LeftAccel, RightAccel, Time, LeftJerk, RightJerk\n");
    for (i = 0; i < length; i++) {
    	Segment l = leftTrajectory[i];
    	Segment r = rightTrajectory[i];
    	fprintf(ptr_file,"%f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f\n", l.x, l.y, r.x, r.y, (i*l.dt), l.velocity, r.velocity, (i*l.dt), l.acceleration, r.acceleration,(i*l.dt), l.jerk, r.jerk);
    }
    fclose(ptr_file);

    /*
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
	fclose(ptr_file);  */


    free(trajectory);

    puts("Press any key to continue.");
    getch();

    return 0;
}
