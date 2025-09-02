import pygame
import sys
import random
timestamps = [7.59, 7.962, 8.383, 8.757, 8.981, 9.175, 9.516, 9.869, 10.274, 10.442, 10.661, 11.048, 11.399, 11.783, 11.929, 12.155, 12.52, 12.923, 13.297, 13.474, 13.706, 14.043, 14.42, 14.786, 14.977, 15.186, 15.578, 15.933, 16.3, 16.479, 16.686, 17.061]

colors = [(255, 0, 0), (0, 255, 0), (0, 0, 255), (255, 255, 0), (255, 0, 255), (0, 255, 255)]

pygame.init()
clock = pygame.time.Clock()
screen = pygame.display.set_mode((400, 300))

font = pygame.font.Font(None, 36)

pygame.mixer.init()
pygame.mixer.music.load("default_file.mp3")
pygame.mixer.music.play()

timestamps.reverse() 
length = len(timestamps) - 1
while True:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            pygame.quit()
            sys.exit()
            
    if pygame.mixer.music.get_pos() != -1:
        current_time = pygame.mixer.music.get_pos() / 1000  # Convert to seconds
        timestamp = timestamps[length]
        if abs(current_time - timestamp) < 0.1:  # If within 100ms of a timestamp
            timestamps.pop(length)
            length -= 1
            screen.fill((0, 0, 0))
            pygame.draw.rect(screen, colors[random.randint(0, 200) % len(colors)], (50, 50 + 0 * 30, 300, 20))
            text = font.render(f"Timestamp: {timestamp:.2f}", True, (255, 255, 255))
            screen.blit(text, (60, 50 + 0 * 30))

    pygame.display.flip()
    clock.tick(60)