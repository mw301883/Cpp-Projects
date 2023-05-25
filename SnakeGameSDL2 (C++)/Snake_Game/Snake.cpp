import Snake;
import Core;
import Time_Counter;
import<deque>;
import<tuple>;
import <algorithm>;
import <string>;
import Button;
import <fstream>;
import External_Functions;
import <SDL_ttf.h>;

Snake::Snake() : PosX(500), PosY(500), Lenght(2), Score(0), Time(0), Direction(DIRECTION::NONE), Speed(40), is_Colision(false), New_Play(true), is_Add_Score(false), is_Minus_Score(false), is_Back_To_Menu(false), /*is_Menu_Animation(true),*/ Counter() {
    this->Collision.Load_Chunk(PATHS::COLLISION_SOUND_PATH);
}

Snake::Snake(SDL_Window* Screen_Window, Texture Game_Texture[SURFACES_TEXTURES_ENUM::TOTAL], SDL_Rect Game_Clips[CLIPS_ENUM::TOTAL]) 
    : Snake_Texture(&Game_Texture[SURFACES_TEXTURES_ENUM::SNAKE]), PosX(500), PosY(500), Lenght(2), Score(0), Time(0), Direction(DIRECTION::NONE), Speed(40), 
    is_Colision(false), New_Play(true), is_Add_Score(false), is_Minus_Score(false), is_Back_To_Menu(false), Counter() {
    SDL_GetWindowSize(Screen_Window, &Screen_Width, &Screen_Height);
    int j = 0;
    for (int i = CLIPS_ENUM::SNAKE_TAIL_DOWN; i < CLIPS_ENUM::OBSTACLE; ++i, ++j) {
        this->Snake_Clips[j] = Game_Clips[i];
    }
    this->Collision.Load_Chunk(PATHS::COLLISION_SOUND_PATH);
}

Snake::~Snake() {
    this->Snake_Texture = nullptr;
}

bool Snake::Render(SDL_Renderer* Renderer) {
    if (this->is_Colision || this->is_Back_To_Menu) {
        return true;
    }
    std::for_each(this->Snake_Body.begin(), this->Snake_Body.end(),
        [&](auto& Segment) {
           Snake_Texture->Render(std::get<0>(Segment), std::get<1>(Segment), Renderer, &std::get<2>(Segment), 0); 
        });
    if (this->Direction == DIRECTION::NONE) {
        this->Snake_Texture->Render(500, 540, Renderer, &this->Snake_Clips[SNAKE_ENUM::SNAKE_TAIL_DOWN], 0);
    }
    return false;
}

void Snake::Check_Events(SDL_Event& Game_Event) {
    if (Game_Event.type == SDL_KEYDOWN && Game_Event.key.repeat == 0 && !this->is_Colision)
    {
        switch (Game_Event.key.keysym.sym)
        {
        case SDLK_UP:
            if(this->Direction != DIRECTION::DOWN)
                this->Direction = DIRECTION::UP;
            break;
        case SDLK_DOWN:
            if (this->Direction != DIRECTION::UP)
                this->Direction = DIRECTION::DOWN;
            break;
        case SDLK_LEFT:
            if (this->Direction != DIRECTION::RIGHT)
                this->Direction = DIRECTION::LEFT;
            break;
        case SDLK_RIGHT:
            if (this->Direction != DIRECTION::LEFT)
                this->Direction = DIRECTION::RIGHT;
            break;
        }
    }
}

void Snake::Grow() {
    ++this->Lenght;
    Add_Score();
}

void Snake::Add_Score() {
    ++this->Score;
    this->is_Add_Score = true;
    this->is_Minus_Score = false;
}

void Snake::Minus_Score() {
    if (this->Score > 0) {
        --this->Score;
        this->is_Minus_Score = true;
        this->is_Add_Score = false;
    }
}

void Snake::Move() {
    switch (this->Direction)
    {
    case DIRECTION::UP: 
        this->PosY -= this->Height;
        Check_If_Collision();
        break;
    case DIRECTION::DOWN:
        this->PosY += this->Height;
        Check_If_Collision();
        break;
    case DIRECTION::RIGHT:
        this->PosX += this->Width;
        Check_If_Collision();
        break;
    case DIRECTION::LEFT:
        this->PosX -= this->Width;
        Check_If_Collision();
        break;
    }
    Set_Segments();
}

void Snake::Set_Segments() {
    //Ustawienie glowy
    std::tuple<int, int, SDL_Rect, int> Next_Segment{ this->PosX, this->PosY, Set_Snake_Head_Clip(), this->Direction };

    //Przesuniecie Snake'a
    this->Snake_Body.push_front(Next_Segment);
    while (this->Snake_Body.size() > this->Lenght) {
        this->Snake_Body.pop_back();
    }

    //Ustawienie Segmentow
    for (int i = 1; i < this->Snake_Body.size() - 1; ++i) {
        SDL_Rect Snake_Segment = Set_Snake_Body_Clip(Calculate_Segment(std::get<3>(this->Snake_Body.at(i - 1)), std::get<3>(this->Snake_Body.at(i))));
        std::get<2>(this->Snake_Body.at(i)) = Snake_Segment;
    }

    //Ustawienie ogonu
    SDL_Rect Snake_Tail = Set_Snake_Tail_Clip(std::get<3>(this->Snake_Body.at(
        [this]() {if (
            Snake_Body.size() == 1) {
        return 0;
        }
        else {
        return static_cast<int>(Snake_Body.size() - 2);
        }
        }())));
    std::get<2>(this->Snake_Body.at(this->Snake_Body.size() - 1)) = Snake_Tail;
}

SDL_Rect Snake::Set_Snake_Head_Clip() {
    switch (this->Direction) {
        case DIRECTION::UP:
            return this->Snake_Clips[SNAKE_ENUM::SNAKE_HEAD_UP];
            break;
        case DIRECTION::DOWN:
            return this->Snake_Clips[SNAKE_ENUM::SNAKE_HEAD_DOWN];
            break;
        case DIRECTION::RIGHT:
            return this->Snake_Clips[SNAKE_ENUM::SNAKE_HEAD_RIGHT];
            break;
        case DIRECTION::LEFT:
            return this->Snake_Clips[SNAKE_ENUM::SNAKE_HEAD_LEFT];
            break;
        default:
            return this->Snake_Clips[SNAKE_ENUM::SNAKE_HEAD_UP];
            break;
    }
}

int Snake::Calculate_Segment(const int& Prev_Pos, const int& Pos) {
    if (Prev_Pos == DIRECTION::UP && Pos == DIRECTION::UP) {
        return 1;
    }
    else if (Prev_Pos == DIRECTION::DOWN && Pos == DIRECTION::DOWN) {
        return 2;
    }
    else if (Prev_Pos == DIRECTION::RIGHT && Pos == DIRECTION::UP) {
        return 3;
    }
    else if (Prev_Pos == DIRECTION::LEFT && Pos == DIRECTION::UP) {
        return 4;
    }
    else if (Prev_Pos == DIRECTION::DOWN && Pos == DIRECTION::RIGHT) {
        return 5;
    }
    else if (Prev_Pos == DIRECTION::DOWN && Pos == DIRECTION::LEFT) {
        return 6;
    }
    else if (Prev_Pos == DIRECTION::LEFT && Pos == DIRECTION::DOWN) {
        return 7;
    }
    else if (Prev_Pos == DIRECTION::RIGHT && Pos == DIRECTION::DOWN) {
        return 8;
    }
    else if (Prev_Pos == DIRECTION::RIGHT && Pos == DIRECTION::RIGHT) {
        return 9;
    }
    else if (Prev_Pos == DIRECTION::LEFT && Pos == DIRECTION::LEFT) {
        return 10;
    }
    else if (Prev_Pos == DIRECTION::UP && Pos == DIRECTION::RIGHT) {
        return 11;
    }
    else if (Prev_Pos == DIRECTION::UP && Pos == DIRECTION::LEFT) {
        return 12;
    }
}

SDL_Rect Snake::Set_Snake_Body_Clip(const int& Clip_Num) {
    if (Clip_Num == 1) {
        return this->Snake_Clips[SNAKE_ENUM::SNAKE_BODY_VER];
    }
    else if (Clip_Num == 2) {
        return this->Snake_Clips[SNAKE_ENUM::SNAKE_BODY_VER];
    }
    else if (Clip_Num == 3) {
        return this->Snake_Clips[SNAKE_ENUM::SNAKE_UP_RIGHT];
    }
    else if (Clip_Num == 4) {
        return this->Snake_Clips[SNAKE_ENUM::SNAKE_UP_LEFT];
    }
    else if (Clip_Num == 5) {
        return this->Snake_Clips[SNAKE_ENUM::SNAKE_UP_LEFT];
    }
    else if (Clip_Num == 6) {
        return this->Snake_Clips[SNAKE_ENUM::SNAKE_UP_RIGHT];
    }
    else if (Clip_Num == 7) {
        return this->Snake_Clips[SNAKE_ENUM::SNAKE_DN_LEFT];
    }
    else if (Clip_Num == 8) {
        return this->Snake_Clips[SNAKE_ENUM::SNAKE_DN_RIGHT];
    }
    else if (Clip_Num == 9) {
        return this->Snake_Clips[SNAKE_ENUM::SNAKE_BODY_HOR];
    }
    else if (Clip_Num == 10) {
        return this->Snake_Clips[SNAKE_ENUM::SNAKE_BODY_HOR];
    }
    else if (Clip_Num == 11) {
        return this->Snake_Clips[SNAKE_ENUM::SNAKE_DN_LEFT];
    }
    else if (Clip_Num == 12) {
        return this->Snake_Clips[SNAKE_ENUM::SNAKE_DN_RIGHT];
    }
}

SDL_Rect Snake::Set_Snake_Tail_Clip(const int& Clip_Num) {
    switch (Clip_Num) {
    case DIRECTION::UP:
        return this->Snake_Clips[SNAKE_ENUM::SNAKE_TAIL_DOWN];
        break;
    case DIRECTION::DOWN:
        return this->Snake_Clips[SNAKE_ENUM::SNAKE_TAIL_UP];
        break;
    case DIRECTION::RIGHT:
        return this->Snake_Clips[SNAKE_ENUM::SNAKE_TAIL_LEFT];
        break;
    case DIRECTION::LEFT:
        return this->Snake_Clips[SNAKE_ENUM::SNAKE_TAIL_RIGHT];
        break;

    }
}

void Snake::Check_If_Collision() {
    if ((this->PosX < 0) || (this->PosX + this->Width > Screen_Width))
    {
        if(!this->is_Colision)
            this->Collision.Play_Chunk();
        this->is_Colision = true;
    }
    else if ((this->PosY < 0) || (this->PosY + this->Height > Screen_Height))
    {
        if(!this->is_Colision)
            this->Collision.Play_Chunk();
        this->is_Colision = true;
    }
    else
    {
        this->New_Play = false;
    }
    std::for_each(this->Snake_Body.begin() + 2, this->Snake_Body.end(), [&,this](auto& Segment) {
        if (std::get<0>(Snake_Body.at(0)) == std::get<0>(Segment) && std::get<1>(Snake_Body.at(0)) == std::get<1>(Segment)) {
            if (!New_Play) {
                this->Collision.Play_Chunk();
                this->is_Colision = true;
            }
            else
            {
                this->New_Play = false;
            }
        }
        });
}

void Snake::Reset() {
    this->PosX = 500;
    this->PosY = 500;
    this->Lenght = 2;
    this->Direction = DIRECTION::NONE;
    this->New_Play = true;
    this->Score = 0;
    this->is_Add_Score = false;
    this->is_Minus_Score = false;
    this->Counter.Reset();
}

int Snake::Get_PosX() {
    return this->PosX;
}

int Snake::Get_PosY() {
    return this->PosY;
}

void Snake::Begining_Text(SDL_Renderer* Renderer, Texture* Text_Texture_White, Texture* Text_Texture_Black) {
    if (this->New_Play) {
        Text_Texture_Black->Render(645, 495, Renderer, nullptr, 0);
        Text_Texture_White->Render(650, 500, Renderer, nullptr, 0);
    }
}

int Snake::Get_Score() {
    return this->Score;
}

void Snake::Set_Score(const int& New_Score) {
    this->Score = New_Score;
}

void Snake::Display_Statis(SDL_Renderer* Renderer, TTF_Font* Font, Texture* Score_White, Texture* Score_Black, Texture* Time_White, Texture* Time_Black) {
    Texture Score_White_Val, Score_Black_Val, Time_White_Val, Time_Black_Val, Add_Score, Minus_Score;
    SDL_Color White{ 224, 224, 224 };
    SDL_Color Black{ 61, 61, 59 };
    SDL_Color Green{ 124,252,0 };
    SDL_Color Red{ 255,0,0 };
    std::string Buff_Str = std::to_string(this->Score);
    Score_White_Val.Create_TTF(Renderer, Font, Buff_Str, White);
    Score_Black_Val.Create_TTF(Renderer, Font, Buff_Str, Black);
    if (this->is_Add_Score) {
        Buff_Str = "+";
        Add_Score.Create_TTF(Renderer, Font, Buff_Str, Green);
        Add_Score.Render(320, 1020, Renderer, nullptr, 0);
    }
    else if(this->is_Minus_Score)
    {
        Buff_Str = "-";
        Minus_Score.Create_TTF(Renderer, Font, Buff_Str, Red);
        Minus_Score.Render(320, 1020, Renderer, nullptr, 0);
    }
    Buff_Str = this->Counter.Return_Time();
    Time_White_Val.Create_TTF(Renderer, Font, Buff_Str, White);
    Time_Black_Val.Create_TTF(Renderer, Font, Buff_Str, Black);
    Score_Black->Render(150, 1020, Renderer, nullptr, 0);
    Score_White->Render(155, 1025, Renderer, nullptr, 0);
    Score_Black_Val.Render(340, 1020, Renderer, nullptr, 0);
    Score_White_Val.Render(345, 1025, Renderer, nullptr, 0);
    Time_Black->Render(600, 1020, Renderer, nullptr, 0);
    Time_White->Render(605, 1025, Renderer, nullptr, 0);
    Time_Black_Val.Render(750, 1020, Renderer, nullptr, 0);
    Time_White_Val.Render(755, 1025, Renderer, nullptr, 0);
}

void Snake::Start_Timer(const int& Prev_Time) {
    if (this->New_Play) {
        this->Counter.Set_Prev_Time(Prev_Time);
    }
    else if(!this->is_Colision){
        this->Counter.Count();
    }
}

bool Snake::Display_GmOv_Statis(SDL_Renderer* Renderer, TTF_Font* Font, Texture* Score_White, Texture* Score_Black, 
    Texture* Time_White, Texture* Time_Black, Texture* Gm_Ov_White, Texture* Gm_Ov_Black, Button& Cancel_Button) {
    if (this->is_Colision) {
        Texture Score_White_Val, Score_Black_Val, Time_White_Val, Time_Black_Val;
        SDL_Color White{ 224, 224, 224 };
        SDL_Color Black{ 61, 61, 59 };
        std::string Buff_Str = std::to_string(this->Score);
        Score_White_Val.Create_TTF(Renderer, Font, Buff_Str, White);
        Score_Black_Val.Create_TTF(Renderer, Font, Buff_Str, Black);

        Buff_Str = this->Counter.Return_Time();
        Time_White_Val.Create_TTF(Renderer, Font, Buff_Str, White);
        Time_Black_Val.Create_TTF(Renderer, Font, Buff_Str, Black);

        Gm_Ov_Black->Render(800, 200, Renderer, nullptr, 0);
        Gm_Ov_White->Render(805, 205, Renderer, nullptr, 0);
        Score_Black->Render(900, 360, Renderer, nullptr, 0);
        Score_White->Render(905, 365, Renderer, nullptr, 0);
        Score_Black_Val.Render(1070, 360, Renderer, nullptr, 0);
        Score_White_Val.Render(1075, 365, Renderer, nullptr, 0);
        Time_Black->Render(900, 460, Renderer, nullptr, 0);
        Time_White->Render(905, 465, Renderer, nullptr, 0);
        Time_Black_Val.Render(1040, 460, Renderer, nullptr, 0);
        Time_White_Val.Render(1045, 465, Renderer, nullptr, 0);

        Cancel_Button.Render(850, 600, Renderer);
        std::ifstream file_i("Records/Records.txt");
        if (file_i.is_open()) {
            std::string last_line{}, Record{};
            while (std::getline(file_i, last_line)) {
                Record = last_line;
            }
            if (Record.length() > 3) {
                int Current_Record = Check_Record_Score(Record[0], Record[1], Record[2]);
                if (this->Score > Current_Record) {
                    Display_New_Record_Text(Renderer, Font);
                }
            }
            file_i.close();
        }
        else if(this->Score != 0){
            Display_New_Record_Text(Renderer, Font);
        }
        this->is_Back_To_Menu = true;
        if (Cancel_Button.Get_is_Clicked()) {
            Cancel_Button.Reset_is_Clicked();
            this->is_Colision = false;
            this->is_Back_To_Menu = false;
            return true;
        }
    }
    return false;
}

std::string Snake::Get_Time() {
    return this->Counter.Return_Time();
}

void Snake::Display_New_Record_Text(SDL_Renderer* Renderer, TTF_Font* Font) {
    SDL_Colour Red{ 255,0,0 };
    SDL_Color Black{ 61, 61, 59 };
    Texture New_Record_Texture_Red, New_Record_Texture_Black;
    New_Record_Texture_Black.Create_TTF(Renderer, Font, TEXT_TTF::NEW_RECORD_TEXT, Black);
    New_Record_Texture_Red.Create_TTF(Renderer, Font, TEXT_TTF::NEW_RECORD_TEXT, Red);
    New_Record_Texture_Black.Render(870, 300, Renderer, nullptr, 0);
    New_Record_Texture_Red.Render(875, 305, Renderer, nullptr, 0);
}