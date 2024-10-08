/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efret <efret@student.19.be>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:34:19 by efret             #+#    #+#             */
/*   Updated: 2024/09/28 00:22:08 by efret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

t_rgb	get_obj_color(t_hit_info hit, t_scene_info scene)
{
	if (hit.obj_type == OBJ_SPHERE)
		return (scene.spheres[hit.obj_index].rgb);
	else if (hit.obj_type == OBJ_PLANE)
		return (scene.planes[hit.obj_index].rgb);
	else if (hit.obj_type == OBJ_CYLINDER)
		return (scene.cylinders[hit.obj_index].rgb);
	else if (hit.obj_type == OBJ_CONE)
		return (scene.cones[hit.obj_index].rgb);
	return ((t_rgb){0, 0, 0,});
}

t_coordinates	get_obj_normal(t_hit_info hit, t_scene_info scene)
{
	if (hit.obj_type == OBJ_SPHERE)
		return (sphere_normal(hit, scene.spheres[hit.obj_index]));
	else if (hit.obj_type == OBJ_PLANE)
		return (scene.planes[hit.obj_index].vector);
	else if (hit.obj_type == OBJ_CYLINDER)
		return (cylinder_normal(hit, scene.cylinders[hit.obj_index]));
	else if (hit.obj_type == OBJ_CONE)
		return (cone_normal(hit, scene.cones[hit.obj_index]));
	return ((t_coordinates){0, 0, 0,});
}

t_material	get_obj_material(t_hit_info hit, t_scene_info scene)
{
	(void)hit, (void)scene;
	return (default_material());
}

t_phong_help_struct	init_phong_struct(
		t_ray ray, t_hit_info hit, t_scene_info scene)
{
	t_phong_help_struct	phong;

	phong.light_dist2 = vec3_dot2(
			vec3_diff(scene.light.coordinates, hit.coordinates));
	phong.ambient = (t_rgb){0, 0, 0};
	phong.specular = (t_rgb){0, 0, 0};
	phong.diffuse = (t_rgb){0, 0, 0};
	phong.hit_material = get_obj_material(hit, scene);
	phong.hit_material.albedo = get_obj_color(hit, scene);
	phong.i_d = color_scalar(scene.light.rgb,
			scene.light.brightness / (4 * M_PI * phong.light_dist2));
	phong.i_s = phong.i_d;
	phong.light_dir = vec3_normalize(
			vec3_diff(scene.light.coordinates, hit.coordinates));
	phong.hit_normal = get_obj_normal(hit, scene);
	phong.reflect_dir = vec3_normalize(
			vec3_diff(
				vec3_scalar(
					phong.hit_normal,
					2 * vec3_dot(phong.light_dir, phong.hit_normal)),
				phong.light_dir));
	phong.view_dir = vec3_neg(ray.dir);
	return (phong);
}

t_rgb	phong_shading(t_ray ray, t_hit_info hit, t_scene_info scene)
{
	t_phong_help_struct	phong;
	t_rgb				hit_color;
	bool				shadow;

	phong = init_phong_struct(ray, hit, scene);
	phong.ambient = color_hadamard(phong.hit_material.albedo,
			color_scalar(scene.a_lighting.rgb,
				scene.a_lighting.ambient_lighting));
	shadow = cast_shadow_ray((t_ray){
			vec3_sum(hit.coordinates, vec3_scalar(phong.hit_normal, 1e-6)),
			phong.light_dir}, scene, sqrt(phong.light_dist2));
	if (!(vec3_dot(phong.hit_normal, phong.light_dir) < 0 || shadow))
	{
		phong.diffuse = color_hadamard(phong.hit_material.albedo,
				color_scalar(phong.i_d,
					fmax(vec3_dot(phong.light_dir, phong.hit_normal), 0.0f)));
		phong.specular = color_scalar(phong.i_s,
				pow(fmax(vec3_dot(phong.reflect_dir, phong.view_dir), 0.0f),
					phong.hit_material.alpha));
	}
	hit_color = color_add(color_scalar(phong.ambient, phong.hit_material.k_a),
			color_add(color_scalar(phong.diffuse, phong.hit_material.k_d),
				color_scalar(phong.specular, phong.hit_material.k_s)));
	return (hit_color);
}
