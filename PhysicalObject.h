/* * Physical objects are objects that can be rendered
 */

#pragma once
#include "Utils.h"
class NPC;
class Wall;

#include <SDL.h>
#include <map>
#include <iostream>
#include <memory>
class PhysicalObject{
public:
  void render_dynamic(SDL_Renderer* renderer_,
          SDL_Texture* texture_,
          const std::map<eTexture, std::map<eDirection, SDL_Rect>>& 
                  dynamic_texture_src_rect_,
          const std::map<eTexture, Vec2di>& textures_render_size_,
          const Vec2df& camera_,
          const float zoom_level_) const;
  
  void render_static(SDL_Renderer* renderer_,
          SDL_Texture* texture_,
          const std::map<eTexture, SDL_Rect>& static_texture_src_rect,
          const std::map<eTexture, Vec2di>& textures_render_size_,
          const Vec2df& camera_,
          const float zoom_level_) const;
  
  void render_burning_flames(SDL_Renderer* renderer_,
          SDL_Texture* texture_,
          const std::map<eTexture, std::map<eDirection, SDL_Rect>>& 
                          dynamic_texture_src_rect_,
          const std::map<eTexture, Vec2di>& textures_render_size_,
          const Vec2df& camera_) const;
  
  const Vec2df move(const float angle_, const float speed, 
                    const std::vector<std::unique_ptr<Wall>>& walls_vector_,
                    const std::vector<std::unique_ptr<NPC>>& npcs_vector_);
  
  template <typename T>
  void checkCollisionWithStuff(const std::vector<T>& stuff_vector_,
                                Vec2df& movement_,
                                const Rect& bounding_box_);
  const Rect* checkCollisionWithBoundingBox(const Rect& future_bbox_, 
                          const Rect& other_bbox, eDirection& direction_);
  
  const Vec2df& getPos() const;
  const Vec2di& getSize() const;
  const Rect& getBoundingBox() const;
  void setDirectionFacing(const Vec2df& movement_);
  
protected:
  //protected constructor ensures BaseObject can't be created alone
  PhysicalObject();
  PhysicalObject(int x_, int y_, eTexture texture_id_, Vec2di size_);
  bool checkCollision(const PhysicalObject& other_) const;
  bool checkCollision(const Rect& bounding_box_) const;
  
  eDirection direction_facing;
  eTexture texture_id;
  eTexture texture_front;
  eTexture texture_back;
  Vec2df pos; 
  Vec2di size;
  Rect bounding_box;
};
