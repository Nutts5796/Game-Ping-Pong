Project Description: “Ping Pong”

📋 About the Project

Ping Pong is a classic console game implemented using the ncurses library. It features a two-player mode where both players can compete on the same device. The goal of the game is to score more points than your opponent by hitting the ball with your paddle.


🎮 Features
    •    Two-player controls:
    •    Left player:
    •    A — move the paddle up.
    •    Z — move the paddle down.
    •    Right player:
    •    K — move the paddle up.
    •    M — move the paddle down.
    •    Realistic physics: the ball bounces off paddles and boundaries with a consistent speed.
    •    Game to 21 points: the winner is declared when one player scores 21 points.
    •    Simple interface: minimalistic ASCII-based design.
    •    Live score display: dynamically updated scoreboard for both players.
    
    🛠️ Technologies Used
    •    C: for the core game logic.
    •    ncurses: for managing the terminal-based graphical interface.
    
    🚀 How to Run the Game
    1.    Ensure ncurses is installed:
    
    •    For Linux:
        sudo apt-get install libncurses5-dev libncursesw5-dev
        
    •    For macOS (via Homebrew):
            brew install ncurses
            
    2.    Compile the project:
            gcc -o main main.c -lncurses
            
    3.    Run the game:
            ./main


🕹️ Rules of the Game
    1.    Players control their paddles using keyboard keys (A/Z for the left player and K/M for the right player).
    2.    The ball starts at the center and bounces off paddles and boundaries.
    3.    If the ball reaches the left or right boundary, the opponent earns a point.
    4.    The first player to score 21 points wins.
    
✨ Potential Improvements
    •    Add a single-player mode with an AI opponent.
    •    Introduce settings for ball speed and field size.
    •    Implement adaptive graphics for larger screens.
    
🤝 Contributing

    Contributions and suggestions are welcome! Feel free to open issues or submit pull requests.
    
🎉 Enjoy the game!
