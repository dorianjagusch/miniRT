#include "minirt.h"

//euclidean norm formula (sqrt(x^2 + y^2 + z^2))
void normalize_ray(t_ray *ray)
{
    double length;
    length = sqrt(ray->direction.x * ray->direction.x + ray->direction.y * ray->direction.y + ray->direction.z * ray->direction.z);
    ray->direction.x /= length;
    ray->direction.y /= length;
    ray->direction.z /= length;
}

t_ray create_primary_ray(t_scene *scene, int row, int column)
{
    t_ray primary_ray;
    double norm_coord_X;
    double norm_coord_Y;
    t_vec3 ray_direction;

    // Calculate the normalized coordinates of the pixel
    norm_coord_X = (2.0 * row) / scene->cam.fov - 1.0;
    norm_coord_Y = 1.0 - (2.0 * column) / scene->cam.fov;
    // Calculate the direction of the primary ray in camera space
    ray_direction.x = scene->cam.dir.x + scene->cam.left.x * norm_coord_X;
    ray_direction.y = scene->cam.dir.y + scene->cam.left.y * norm_coord_X;
    ray_direction.z = scene->cam.dir.z + scene->cam.left.z * norm_coord_X;
    // Normalize the ray direction- //euclidean norm formula (sqrt(x^2 + y^2 + z^2))
    normalize(ray_direction);
    // Set the origin and direction of the primary ray
    primary_ray.origin = scene->cam.pos;
    primary_ray.direction = ray_direction;
    return (primary_ray);
}

// Create an image array to store the pixel values
void renderScene(t_img img)
{
    int img_height;
    int img_width;
    int count;
    t_ray primary_ray;

    count = 0;
    img_height = 0;
    img_width = 0;

while (img_height < HEIGHT)
{   
    img_width = 0;
    while (img_width < WIDTH)
    {
        // Compute ray direction
        primary_ray = create_primary_ray(img->scene, img_height, img_width);
        // Search for the closest intersection
         t_vec3 hitpoint; // position hit
         t_vec3 hitnorm;// normalized hit
        // double minDistance = LARGE NUMBER;
        // t_obj* object = NULL; // need to identify the objects etc
        // 
        // while (count < img->scene->n_objs) {
        //     if (Intersect(scene->objs[count], primary_ray, &pHit, &nHit)) {
        //         double distance = Distance(scene->cam.pos, pHit);
        //         if (distance < minDistance) {
        //             object = &scene->objs[count];
        //             minDistance = distance;
        //         }
        //     }
        //     count++;
        // }
        //check if its an object
        if (object != NULL) {
            // Compute illumination
            t_ray shadowRay;
            shadowRay.direction = t_vec3_sub(scene->light.pos, pHit);
            bool isInShadow = false; // write this function
            count = 0;
            while (count < scene->n_objs) {
                if (Intersect(scene->objs[count], shadowRay)) {
                    isInShadow = true;
                    break;
                }
                count++;
            }
            if (!isInShadow)
            {
                // Apply object color and light brightness
                //mlx_put_pixel to image? object->colour * scene->light.brightness
            }
            else
                //mlx_put_pixel to image,  No illumination in shadow
        }
        else
        {
            //mlx_put_pixel to image  No intersection, set pixel to ambient
        }
        img_width++;
    }
    img_height++;
    }
}

