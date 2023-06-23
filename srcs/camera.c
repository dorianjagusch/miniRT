#include "minirt.h"

/*Calculate the camera's basis vectors:

The forward vector is computed by subtracting the camera's position (scene->cam.pos) from its target (scene->cam.target).
It represents the direction the camera is facing.
The right vector is obtained by taking the cross product of the camera's up vector (scene->cam.up) and the forward vector.
It determines the rightward direction relative to the camera's orientation.
The up vector is calculated by crossing the forward vector with the right vector. It represents the upward direction relative to the camera's orientation.
Normalize the basis vectors:

To ensure that the basis vectors have a unit length, each of them is normalized using the vec3_normalize function. This step is essential for accurate transformations.
Construct the camera-to-world matrix:
The camera-to-world matrix is a 4x4 matrix represented by scene->cam.camera_to_world.
The first three columns of the matrix correspond to the right, up, and forward vectors, respectively.
The fourth column stores the camera's position, scene->cam.pos.
By constructing the camera-to-world matrix, you have a transformation matrix that allows you to convert points and vectors from camera space to world space
This matrix is then used in the create_primary_ray function to transform the ray direction from camera space to world space,
ensuring accurate mapping of coordinates in the ray-tracing process.*/

//responsible for constructing the camera-to-world matrix,
//which transforms points and vectors from camera space to world space
void init_camera_dir(t_camera *cam)
{
    cam->forward = vec3_sub(cam->target, cam->pos);//
    cam->right = vec3_cross(cam->up, cam->forward);
    cam->up = vec3_cross(forward, cam->right);
	cam->aspect_ratio = (double)WIDTH / (double)HEIGHT;
    vec3_normalize(&cam->forward);
    vec3_normalize(&cam->right);
    vec3_normalize(&cam->up);
}

t_ray create_primary_ray(t_camera *cam, t_vec2 pxl)
{
    t_ray primary_ray;
    double norm_coord_X;
    double norm_coord_Y;

    norm_coord_X = (2.0 * pxl.x) / (double) WIDTH - 1.0;
    norm_coord_Y = 1.0 - (2.0 * pxl.y) / (double) HEIGHT;
    // Transform the normalized coordinates to world space using the camera-to-world matrix, in theory
    primary_ray.dir = vec3_add(cam.forward, vec3_add(vec3_scale(cam->right, norm_coord_X), vec3_scale(cam->up, norm_coord_Y))); //seperate calcs
    normalize(primary_ray.dir);
    primary_ray.origin = cam->pos;
    return (primary_ray);
}


