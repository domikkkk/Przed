#include <SFML/Graphics.hpp>
#include <vector>
#include "Triangulate.hpp"
#include "Terrain.hpp"
#include <cmath>
#include <iostream>

#define PI 3.14159

float Vectof2f_mag(sf::Vector2f v)
{
    return std::sqrt(v.x * v.x + v.y * v.y);
}

/// <summary>
/// Smooth terrain generation
/// </summary>
/// <param name="terrain_size">amount of units to generate</param>
/// <param name="density">units per vertex, the bigger the less precise it is</param>
/// <returns></returns>
Vector2dVector Terrain::GenerateRandom(unsigned terrain_size, unsigned density)
{
    Vector2dVector generated;
    float base = (rand() % terrain_size / 4.f) + 300;
    float accel = (rand() % 4) - 2;
    float step = (rand() % 10) - 5;
    for (unsigned i = 0; i <= (terrain_size / density) + 1; i++)
    {
        step += accel / 20;
        base += step;
        generated.push_back(sf::Vector2f(i * density, base));
        accel = ((rand() % 5) - 2) * (int)density;
    }
    generated.push_back(sf::Vector2f(terrain_size + 1000, base));
    generated.push_back(sf::Vector2f(terrain_size + 1000, terrain_size + 1000));
    generated.push_back(sf::Vector2f(0, terrain_size + 1000));
    return generated;
}

//square debug
//Vector2dVector Terrain::GenerateRandom(unsigned terrain_size, unsigned density)
//{
//    Vector2dVector generated;
//    generated.push_back(sf::Vector2f(0, 400));
//    generated.push_back(sf::Vector2f(250, 50));
//    generated.push_back(sf::Vector2f(200, 0));
//    generated.push_back(sf::Vector2f(250, 0));
//    generated.push_back(sf::Vector2f(500, 200));
//    generated.push_back(sf::Vector2f(500, 500));
//    generated.push_back(sf::Vector2f(100, 500));
//    return generated;
//}

// numerical approach, finds intersection between O and line formed by p1 p2
// if two intersection points exist, it returns random one
sf::Vector2f Intersection(sf::Vector2f O, sf::Vector2f p1, sf::Vector2f p2, float r)
{
    sf::Vector2f parameter = p1 - p2;
    sf::Vector2f full = p1 - p2;
    int div = 1;
    for (int i = 0; i < 8; i++)
    {
        sf::Vector2f divided = { full.x / div, full.y / div };
        sf::Vector2f temp = p2 + parameter;
        if (Vectof2f_mag(temp - O) > r)
            parameter += divided;
        else
            parameter -= divided;
        div *= 2;
    }
    return p2 + parameter;
}

void Terrain::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // render everything inside tri list
    for (auto& tri : tris)
        target.draw(tri);
}

// recalculates render_terrain when it's needed, for example after a bomb hit.
// it creates new Drawable objects and assigns the texture
void Terrain::update_geo()
{
    tris.clear(); // forget everything

    Vector2dVector triangulate_output; // temp vector to store triangulated vertices
    // run triangulation
    Triangulate::Process(raw_vertices, triangulate_output);
    //create sfml triangles out of that, and remember
    for (unsigned i = 0; i < triangulate_output.size() / 3; ++i)
    {
        sf::ConvexShape poly(3);

        poly.setPoint(0, sf::Vector2f(triangulate_output[3 * i].x, triangulate_output[3 * i].y));
        poly.setPoint(1, sf::Vector2f(triangulate_output[3 * i + 1].x, triangulate_output[3 * i + 1].y));
        poly.setPoint(2, sf::Vector2f(triangulate_output[3 * i + 2].x, triangulate_output[3 * i + 2].y));
        poly.setTexture(&texture);

        // get the global bounding rect
        sf::FloatRect bounds = poly.getGlobalBounds();
        bounds.top *= textureScale;
        bounds.left *= textureScale;
        bounds.width *= textureScale;
        bounds.height *= textureScale;
        // turn to float
        sf::IntRect textureRect(bounds);

        // trim texture to use only that part
        poly.setTextureRect(textureRect);
        tris.push_back(poly); // copy this to a vector
    }
    std::cout << "tri: " << tris.size() << ", vertex: " << raw_vertices.size() << std::endl;
}

void Terrain::MakeHole(float x, float y, float r)
{
    return MakeHole(sf::Vector2f(x, y), r); // make vec2f and call the other overload

}



static bool once = false;
//1. find out which vertices will be deleted by bomb
//2. find intersection between floor and radius border
//3. place new vertices at these intersecitons and remove everything between
//4. place a ring of vertices along the perimeter
// this doesn't work for a) more than 2 intersections b) cutting off parts of land
void Terrain::MakeHole(sf::Vector2f pos, float r)
{
    Vector2dVector::iterator last_removed_iter; // iterator pointing to place where to insert crater
    Vector2dVector::iterator begin_erase, end_erase; //region to remove by bomb
    //^ this erases floating parts, because triangulation can't handle it
    sf::Vector2f ring_start, ring_end; // x,y position of crater main points
    bool once = true;
    bool collided = false;

    // find first and last vertex iterator to remove (end iterator is not inclusive)
    // first and last are forbidden to be removed for safety, and simplifies code
    for (auto it = raw_vertices.begin(); it < raw_vertices.end(); ++it)
    {
        // stay inside this loop when a vertex inside hole radius is found
        if (Vectof2f_mag(pos - *it) <= r)
        {
            collided = true; // means that the bomb must have hit something
            if (once)
            {
                once = false;
                begin_erase = it;
            }
            end_erase = it;
        }
    }


    // generate vertices and add before the last one
    // get angle from center of bomb to start
    if (collided)
    {

        // find start and end intersection
        Vector2dVector::iterator find_intersect_between_this; // edge cases...
        if (begin_erase == raw_vertices.begin())
            // if first element is being removed, make bridge between this and last, like circullar list?
            find_intersect_between_this = raw_vertices.end() - 1;
        else
            find_intersect_between_this = begin_erase - 1;
        ring_start = Intersection(pos, *begin_erase, *find_intersect_between_this, r);

        if (end_erase == raw_vertices.end() - 1)
            find_intersect_between_this = raw_vertices.begin();  // if last is being removed
        else
            find_intersect_between_this = end_erase + 1;

        ring_end = Intersection(pos, *end_erase, *find_intersect_between_this, r);
        last_removed_iter = raw_vertices.erase(begin_erase, end_erase + 1);

        double angle_start = atan2(pos.y - ring_start.y, pos.x - ring_start.x);
        //std::cout << "start: " << angle_start << "\n";
        double angle_end = atan2(pos.y - ring_end.y, pos.x - ring_end.x);
        //std::cout << "end: " << angle_end << "\n";
        last_removed_iter = raw_vertices.insert(last_removed_iter, ring_start);
        if (angle_end > angle_start)
        {
            angle_end -= 2 * PI;
        }
        while (true)
        {
            angle_start -= 8 / r; // !!ARBITRARY!!
            if (angle_start < angle_end) break;
            sf::Vector2f direction(-r * cos(angle_start), -r * sin(angle_start));
            last_removed_iter = raw_vertices.insert(++last_removed_iter, pos + direction);
        }
        raw_vertices.insert(++last_removed_iter, ring_end);
        this->update_geo();
    }
}

// get exact height on a line projected from point over it
float HeightLerp(Vector2dVector::iterator left, Vector2dVector::iterator right, sf::Vector2f pos)
{
    float x_length = right->x - left->x; //x delta of the line joining two vertices
    float y_length = right->y - left->y; //y delta of the line joining two vertices

    float xdist = pos.x - left->x; // this is the actual lenght

    return (xdist / x_length) * y_length + left->y; //move from prev to next on ypos by the ratio
}

// since vertices come from left to right, if vertex x changes from less to more than mouse,
// this means it's floor, if it changes from more to less then it's ceiling
// so it's possible to tell which two vertices under some specific Y coordinate can form a floor
// by tracking how the relation changes


std::pair<float, float> Terrain::FloorHeight(sf::Vector2f pos, bool allowCeiling)
{
    float default_floor =  -10000; // means there is no floor under an object
    float default_angle = 0;
    std::pair<float, float> default_result{default_floor, default_angle};
    std::pair<float, float> result{10000, 0};
    if (raw_vertices.size() < 2) return default_result;
    auto prev = raw_vertices.begin(); // there's no floor at the edge anyway
    auto iter = prev+1;

    bool floor = false; // because the alghoritm detects any line under X coordinate, this flag
                // says if it's a floor or ceiling

    float closest_max_height = 10000; //height of closest floor/ceiling (higher of the two vertices)
    //go over whole list
    while (true)
    {
        // vertices start from left border, therefore I assume at the beginning
        // the x coordinate in question is further down the list
        Vector2dVector::iterator closest = raw_vertices.end(); //initialised to invalid value
        while (true) // if object is under floor then pos.y > floor.y
        {
            float curHeight = HeightLerp(prev, iter, pos);
            if (pos.y < curHeight)
            {
                if (closest == raw_vertices.end() || result.first > curHeight) // if not set or better
                {
                    // if now the vertex is to the right of pos, and previously it wasn't,
                    // it must be floor, iter-1 is always safe here
                    if (pos.x >= (prev)->x && pos.x < iter->x)
                    {
                        //std::cout << "floor\n";
                        floor = true;
                        closest = iter;
                        result.first = curHeight;
                        result.second = -std::atan((iter->y - prev->y) / ((iter)->x - prev->x));
                    }
                    else if (pos.x < (prev)->x && pos.x >= iter->x) // if this is true then it's a ceiling
                    {
                        //std::cout << "ceil\n";
                        floor = allowCeiling;
                        closest = iter;
                        result.first = curHeight;
                        result.second = std::atan((iter->y - prev->y) / ((iter)->x - prev->x));
                    }
                    // otherwise it isn't correct point at all
                }
            }
            prev = iter++;
            if (iter == raw_vertices.end())
            {
                if (closest == iter) //still found nothing
                    return default_result;
                break; // otherwise stop searching
            }
        }

        if (!floor)
            return default_result;

        iter = closest;
        if (iter == raw_vertices.end() || iter == raw_vertices.begin()) return default_result;
        return floor ? result : default_result;

    }
    return default_result;
}