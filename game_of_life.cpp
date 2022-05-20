#include "game_of_life.h"

GameOfLife::GameOfLife(int h, int w)  {
        Initialize(h, w);
}

GameOfLife::GameOfLife(int h, int w, const std::vector<std::pair<int, int>>& points) :
        h_(h),
        w_(w) {
    curr_grid_.resize(h + 2, std::vector<Point>(w + 2, Point::kEmpty));
    prev_grid_.resize(h + 2, std::vector<Point>(w + 2, Point::kEmpty));

    for (const auto& point : points) {
        prev_grid_[point.first][point.second] = Point::kFull;
    }
}

void GameOfLife::Initialize(int h, int w) {
    h_ = h;
    w_ = w;
    curr_grid_.resize(h + 2, std::vector<Point>(w + 2, Point::kEmpty));
    prev_grid_.resize(h + 2, std::vector<Point>(w + 2, Point::kEmpty));

    srand(time(0));
    for (int i = 1; i <= h_; ++i) {
        for (int j = 1; j <= w_; ++j) {
            if(rand() % 5 < 2) {
                prev_grid_[i][j] = Point::kFull;
            }
        }
    }
}

void GameOfLife::CreateWindow() {
    const int SCREEN_WIDTH = 10*w_;
    const int SCREEN_HEIGHT = 10*h_;

    if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
    } else {
        window_ = SDL_CreateWindow("GAME OF LIFE", SDL_WINDOWPOS_CENTERED_MASK, SDL_WINDOWPOS_CENTERED_MASK, SCREEN_WIDTH,
                                  SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        screenSurface_ = SDL_GetWindowSurface( window_ );
    }
}

void GameOfLife::Print() const {
    SDL_Rect rect {0, 0, 0, 0};
    SDL_FillRect( screenSurface_, nullptr, SDL_MapRGB( screenSurface_->format, 0x00, 0x00, 0x00 ) );
    for (int i = 1; i <= h_; ++i) {
        for (int j = 1; j <= w_; ++j) {
            if (prev_grid_[i][j] == Point::kFull) {
                rect = SDL_Rect{(j -1) * 10, (i-1) * 10, 10, 10};
                SDL_FillRect( screenSurface_, &rect, SDL_MapRGB( screenSurface_->format, 0xFF, 0xFF, 0xFF ) );
            }
        }
    }
    SDL_Delay( 250);
    SDL_UpdateWindowSurface( window_ );
}

bool GameOfLife::PassOneSession() {
    Print();
    for (int i = 1; i <= h_; ++i) {
        for (int j = 1; j <= w_; ++j) {
            int cnt = 0;
            for (int k = i - 1; k <= i + 1; ++k) {
                for (int t = j - 1; t <= j + 1; ++t) {
                    if (k == i && t == j) {
                        continue;
                    }
                    if (prev_grid_[k][t] == Point::kFull) {
                        ++cnt;
                    }
                }
            }

            if (prev_grid_[i][j] == Point::kFull) {
                if (cnt < 2 || cnt > 3) {
                    curr_grid_[i][j] = Point::kEmpty;
                } else {
                    curr_grid_[i][j] = Point::kFull;
                }
            } else if (prev_grid_[i][j] == Point::kEmpty) {
                if (cnt == 3) {
                    curr_grid_[i][j] = Point::kFull;
                } else {
                    curr_grid_[i][j] = Point::kEmpty;
                }
            }
        }
    }
    if (prev_grid_ == curr_grid_) {
        return true;
    }
    prev_grid_ = curr_grid_;
    return false;
}

int GameOfLife::Run() {
    bool is_end = false;
    CreateWindow();
    SDL_Event evt;

    while (!is_end) {
        is_end = PassOneSession();
        if(SDL_PollEvent(&evt)) {
            if(evt.type == SDL_QUIT) {
                is_end = true;
            }
        }
    }
    SDL_Quit();
    return 0;
}