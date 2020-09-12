/*******************************************************************************************
*
*   raylib [textures] example - Texture loading and drawing a part defined by a rectangle
*
*   This example has been created using raylib 1.3 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2014 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

use raylib::prelude::*;

const MAX_FRAME_SPEED 15 const MIN_FRAME_SPEED 1

    int
    main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    let screen_width = 800;
    let screen_height = 450;

    rl.set_window_size(screen_width, screen_height);
    rl.set_window_title(thread, "raylib [texture] example - texture rectangle");


    // NOTE: Textures MUST be loaded after Window initialization (OpenGL context is required)
    Texture2D scarfy = LoadTexture("resources/scarfy.png"); // Texture loading

    Vector2 position = {350.0, 280.0};
    Rectangle frameRec = {0.0, 0.0, (float)scarfy.width / 6, (float)scarfy.height};
    int currentFrame = 0;

    int framesCounter = 0;
    int framesSpeed = 8; // Number of spritesheet frames shown by second

    rl.set_target_fps(60); // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    return Box::new(move |rl: &mut RaylibHandle, thread: &RaylibThread| -> () // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        framesCounter++;

        if (framesCounter >= (60 / framesSpeed))
        {
            framesCounter = 0;
            currentFrame++;

            if (currentFrame > 5)
                currentFrame = 0;

            frameRec.x = (float)currentFrame * (float)scarfy.width / 6;
        }

        if (IsKeyPressed(raylib::consts::KeyboardKey::KEY_RIGHT))
            framesSpeed++;
        else if (IsKeyPressed(raylib::consts::KeyboardKey::KEY_LEFT))
            framesSpeed--;

        if (framesSpeed > MAX_FRAME_SPEED)
            framesSpeed = MAX_FRAME_SPEED;
        else if (framesSpeed < MIN_FRAME_SPEED)
            framesSpeed = MIN_FRAME_SPEED;
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        let mut d = rl.begin_drawing(thread);

        d.clear_background(Color::RAYWHITE);

        DrawTexture(scarfy, 15, 40, WHITE);
        d.draw_rectangle_lines(15, 40, scarfy.width, scarfy.height, Color::LIME);
        d.draw_rectangle_lines(15 + frameRec.x, 40 + frameRec.y, frameRec.width, frameRec.height,Color::RED);

        d.draw_text("FRAME SPEED: ", 165, 210, 10, Color::DARKGRAY);
        d.draw_text(FormatText("%02i FPS", framesSpeed), 575, 210, 10, Color::DARKGRAY);
        d.draw_text("PRESS RIGHT/LEFT KEYS to CHANGE SPEED!", 290, 240, 10, Color::DARKGRAY);

        for (int i = 0; i < MAX_FRAME_SPEED; i++)
        {
            if (i < framesSpeed)
                d.draw_rectangle(250 + 21 * i, 205, 20, 20,Color::RED);
            d.draw_rectangle_lines(250 + 21 * i, 205, 20, 20, Color::MAROON);
        }

        DrawTextureRec(scarfy, frameRec, position, WHITE); // Draw part of the texture

        d.draw_text("(c) Scarfy sprite by Eiden Marsal", screen_width - 200, screen_height - 20, 10, Color::GRAY);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(scarfy); // Texture unloading

    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}