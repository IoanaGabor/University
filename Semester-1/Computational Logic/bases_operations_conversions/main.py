"""
@author: Ioana Gabor
"""
from consoleUI import ConsoleUI
from conversions import Conversions
from operations import Operations

if __name__ == "__main__":
    operations = Operations()
    conversions = Conversions()
    console = ConsoleUI(operations, conversions)
    console.run_menu()
