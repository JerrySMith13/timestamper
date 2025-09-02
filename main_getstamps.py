import sys
import os
import pygame

class Timestamps:
    start: float
    end: float
    timestamps: list[float]

file_name = sys.argv[1] if len(sys.argv) > 1 else "default_file.mp3"
file_name = os.path.abspath(file_name)

pygame.init()
screen = pygame.display.set_mode((400, 300))

pygame.mixer.init()
pygame.mixer.music.load(file_name)

pygame.font.init()
font = pygame.font.Font(None, 36)
pause_msg = font.render("press play to resume", True, (255, 255, 255))
play_msg = font.render("press pause to stop", True, (255, 255, 255))

paused = False

timestamps = []

pygame.mixer.music.play()
while True:
    for event in pygame.event.get():
    
        if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_SPACE:
                if paused:
                    paused = False
                    pygame.mixer.music.unpause()
                    screen.fill((0, 0, 0))
                    screen.blit(play_msg, (20, 20))
                else:
                    paused = True
                    pygame.mixer.music.pause()
                    screen.fill((0, 0, 0))
                    screen.blit(pause_msg, (20, 20))
            if event.key == pygame.K_w:
                if not paused:
                    timestamps.append(pygame.mixer.music.get_pos() / 1000)
                    print("timestamp added:", timestamps[-1])
        if event.type == pygame.QUIT:
            pygame.mixer.music.stop()
            pygame.quit()
            print(timestamps)
            sys.exit()
    pygame.display.flip()
    pygame.time.Clock().tick(120)

