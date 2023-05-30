/* Create a polygon in 2D plane
   Demonstrate usage of sturct, pointer, malloc and free
   Emad Arasteh
   Feb 17 , 2022
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// Struct to represent a point in 2D plane
typedef struct
{
  int x;
  int y;
} point_t;

// Struct to represent a polygon in 2D plane
typedef struct
{
  unsigned int nr_vertices;
  point_t      *coords;
} polygon_t;


polygon_t *create_polygon(unsigned int nr_vertices)
{

  polygon_t *polygon;

  polygon = malloc(sizeof(polygon_t));

  if(!polygon)
  {
    return NULL;
  }

  polygon->nr_vertices = nr_vertices;

  polygon->coords = malloc(sizeof(point_t) * nr_vertices);

  if(!polygon->coords)
  {
  	free(polygon);
	return NULL;
  }

  return polygon;

}

void delete_polygon(polygon_t *polygon)
{
  // check if polygon and its coordinates has valid pointers
  assert(polygon);
  assert(polygon->coords);
  free(polygon->coords);
  free(polygon);
}

// Set the value of the x-coordinate for a specific vertex
void set_coordinate_x(polygon_t *polygon, unsigned int vertex_nr, int val)
{
  assert(polygon);
  assert(polygon->coords);
  // check if vertex nr is less than total number of vertices in the polygon
  assert(vertex_nr < polygon->nr_vertices);

  polygon->coords[vertex_nr].x = val;
}

void set_coordinate_y(polygon_t *polygon, unsigned int vertex_nr, int val)
{
  assert(polygon);
  assert(polygon->coords);
  assert(vertex_nr < polygon->nr_vertices);
  polygon->coords[vertex_nr].y = val;
}


int get_coordinate_x(polygon_t *polygon, unsigned int vertex_nr)
{
  assert(polygon);
  assert(polygon->coords);
  assert(vertex_nr < polygon->nr_vertices);
  return polygon->coords[vertex_nr].x;
}

int get_coordinate_y(polygon_t *polygon, unsigned int vertex_nr)
{
  assert(polygon);
  assert(polygon->coords);
  assert(vertex_nr < polygon->nr_vertices);
  return polygon->coords[vertex_nr].y;
}

int get_nr_vertices(polygon_t *polygon)
{
  assert(polygon);
  assert(polygon->coords);
  return polygon->nr_vertices;
}

// Display coordinates of the polygon
void display(polygon_t *polygon)
{
  assert(polygon);
  assert(polygon->coords);

  printf("Coordinates of the polygon are:\n");

  int i;
  for(i = 0; i< get_nr_vertices(polygon); i++)
  {
    printf("  (X,Y) : (%d, %d)\n", get_coordinate_x(polygon, i), get_coordinate_y(polygon, i));
  }
}

int main()
{

  polygon_t *rect;

  rect = create_polygon(4);

  if (rect == NULL)
  {
    printf("Error: couldn't create a polygon\n");
  }

  point_t rect_points[4] = { {6, 8}, {6, 14}, {8, 8}, {8, 14} };

  // set the x- and y-coordinates of the rectangle
  int i = 0;
  for(i = 0; i< get_nr_vertices(rect); i++)
  {
    set_coordinate_x(rect, i, rect_points[i].x);
    set_coordinate_y(rect, i, rect_points[i].y);
  }

  display(rect);

  delete_polygon(rect);

  return 0;
}
