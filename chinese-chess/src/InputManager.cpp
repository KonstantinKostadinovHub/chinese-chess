#include "InputManager.h"

const Uint8* InputManager::m_keyboardState = new Uint8;
int2 InputManager::m_mouseCoor = int2();
bool InputManager::m_mouseIsPressed = bool();
bool InputManager::m_mouseIsDoubleClicked = bool();
bool InputManager::m_mouseOnClick = bool();
bool InputManager::m_mouseOnRelease = bool();
bool InputManager::m_mouseIsPressedPrevFrame = bool();
bool InputManager::m_mouseIsHolded = bool();

InputManager::InputManager()
{

}

InputManager::~InputManager()
{
    delete m_keyboardState;
}

void InputManager::setMouseMultiply(float2 multiplier)
{
    m_mouseMultiply.x = multiplier.x;
    m_mouseMultiply.y = multiplier.y;
}

void InputManager::handleInput()
{
    m_mouseIsPressed = false;
    m_mouseIsDoubleClicked = false;
    
    while (SDL_PollEvent(&m_event))
    {
        switch (m_event.type)
        {
		case SDL_MOUSEMOTION:
            SDL_GetMouseState(&(m_mouseCoor.x), &(m_mouseCoor.y));
			
            m_mouseCoor.x *= m_mouseMultiply.x;
            m_mouseCoor.y *= m_mouseMultiply.y;

            break;
        case SDL_MOUSEBUTTONDOWN:
            if (m_event.button.button == SDL_BUTTON_LEFT)
            {
                m_mouseIsPressed = true;
            }
            break;
        }
    }

    m_keyboardState = SDL_GetKeyboardState(NULL);
	
    if (m_mouseIsPressed)
    {
        if (!m_mouseIsPressedPrevFrame)
        {
            m_mouseOnClick = true;
        }
        else
        {
            m_mouseOnClick = false;
        }
        
        m_mouseIsHolded = true;
    }
    else
    {
        m_mouseIsPressedPrevFrame = false;
        m_mouseOnClick = false;
    }
}

bool InputManager::mouseIsPressed()
{
    return m_mouseIsPressed;
}

bool isMouseInRect(SDL_Rect rect)
{
    return MouseIsInRect(InputManager::m_mouseCoor, rect);
}


bool mouseIsPressed()
{
    return InputManager::mouseIsPressed();
}

bool isAnyKeyPressed()
{
    int numOfKeys = 322;

    for (int i = 0; i < numOfKeys; i++)
    {
        if (InputManager::m_keyboardState[i])
        {
            return true;
        }
    }
    return false;
}
