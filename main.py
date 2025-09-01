import sys
import os
import pygame

POSSIBLE_MODES = ['args', 'file', 'input']
MODE = "args"

class Settings:
    input_file: str | None
    output_file: str | None
    start_time: float | None
    end_time: float | None

    def __init__(self):
        if MODE == "args":
            pass
        elif MODE == "file":
            pass
        elif MODE == "input":
            pass

class Timestamps:
    start: float
    end: float
    timestamps: list[float]




file_name = sys.argv[1] if len(sys.argv) > 1 else "default_file.mp3"
file_name = os.path.abspath(file_name)

pygame.mixer.init()
pygame.mixer.music.load(file_name)
pygame.mixer.music.play()

while pygame.mixer.music.get_busy():
    pygame.time.Clock().tick(10)