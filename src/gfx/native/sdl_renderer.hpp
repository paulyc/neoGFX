// sdl_renderer.hpp
/*
  neogfx C++ GUI Library
  Copyright (c) 2015 Leigh Johnston.  All Rights Reserved.
  
  This program is free software: you can redistribute it and / or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.
  
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  
  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include <neogfx/neogfx.hpp>
#include <set>
#include <map>
#include "opengl_renderer.hpp"
#include <neogfx/app/i_basic_services.hpp>
#include <neogfx/hid/keyboard.hpp>

namespace neogfx
{
	class i_native_surface;

	class sdl_renderer : public opengl_renderer
	{
	public:
		struct unsupported_renderer : std::runtime_error { unsupported_renderer() : std::runtime_error("neogfx::sdl_renderer::unsupported_renderer") {} };
		struct failed_to_activate_gl_context : std::runtime_error { failed_to_activate_gl_context(const std::string& aReason) : std::runtime_error("neogfx::sdl_renderer::failed_to_activate_gl_context: " + aReason) {} };
		struct failed_to_create_system_cache_window : std::runtime_error { failed_to_create_system_cache_window(const std::string& aReason) : std::runtime_error("neogfx::sdl_renderer::failed_to_create_system_cache_window: " + aReason) {} };
	public:
		sdl_renderer(neogfx::renderer aRenderer, bool aDoubleBufferedWindows, i_basic_services& aBasicServices, i_keyboard& aKeyboard);
		~sdl_renderer();
	public:
		bool double_buffering() const override;
		const i_native_surface* active_context_surface() const override;
		void activate_context(const i_native_surface& aSurface) override;
		void deactivate_context() override;
		opengl_context create_context(const i_native_surface& aSurface) override;
		void destroy_context(opengl_context aContext) override;
		std::unique_ptr<i_native_window> create_window(i_surface_manager& aSurfaceManager, i_surface_window& aWindow, const video_mode& aVideoMode, const std::string& aWindowTitle, window_style aStyle) override;
		std::unique_ptr<i_native_window> create_window(i_surface_manager& aSurfaceManager, i_surface_window& aWindow, const size& aDimensions, const std::string& aWindowTitle, window_style aStyle) override;
		std::unique_ptr<i_native_window> create_window(i_surface_manager& aSurfaceManager, i_surface_window& aWindow, const point& aPosition, const size& aDimensions, const std::string& aWindowTitle, window_style aStyle) override;
		std::unique_ptr<i_native_window> create_window(i_surface_manager& aSurfaceManager, i_surface_window& aWindow, i_native_surface& aParent, const video_mode& aVideoMode, const std::string& aWindowTitle, window_style aStyle) override;
		std::unique_ptr<i_native_window> create_window(i_surface_manager& aSurfaceManager, i_surface_window& aWindow, i_native_surface& aParent, const size& aDimensions, const std::string& aWindowTitle, window_style aStyle) override;
		std::unique_ptr<i_native_window> create_window(i_surface_manager& aSurfaceManager, i_surface_window& aWindow, i_native_surface& aParent, const point& aPosition, const size& aDimensions, const std::string& aWindowTitle, window_style aStyle) override;
		bool creating_window() const override;
	public:
		void render_now() override;
		bool use_rendering_priority() const override;
	public:
		virtual bool process_events();
	private:
		opengl_context create_context(void* aNativeSurfaceHandle);
		static int filter_event(void* aSelf, SDL_Event* aEvent);
		bool queue_events();
	private:
		bool iDoubleBuffering;
		i_basic_services& iBasicServices;
		i_keyboard& iKeyboard;
		void* iSystemCacheWindowHandle;
		opengl_context iContext;
		uint32_t iCreatingWindow;
		const i_native_surface* iActiveContextSurface;
	};
}