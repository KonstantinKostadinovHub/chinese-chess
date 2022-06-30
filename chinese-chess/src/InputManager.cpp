#include "InputManager.h"

const Uint8* InputManager::m_keyboardState = new Uint8;
int2 InputManager::m_mouseCoor = int2();
bool InputManager::m_mouseIsPressed = bool();
bool InputManager::m_mouseIsDoubleClicked = bool();
bool InputManager::m_mouseOnClick = bool();
bool InputManager::m_mouseOnRelease = bool();
bool InputManager::m_mouseIsRightPressed = bool();
bool InputManager::m_mouseIsPressedPrevFrame = bool();
bool InputManager::m_mouseIsHolded = bool();

InputManager::InputManager()
{
    m_scroll = 0;
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
    m_mouseIsRightPressed = false;
    
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

            if (m_event.button.button == SDL_BUTTON_RIGHT)
            {
                m_mouseIsRightPressed = true;
            }

            break;
        case SDL_TEXTINPUT:

            if (m_event.type == SDL_KEYDOWN && m_event.key.keysym.sym == SDLK_BACKSPACE && m_textInput.length() > 0)
            {
                m_textInput = m_textInput.substr(0, m_textInput.length() - 1);
            }
            if (m_event.type == SDL_TEXTINPUT)
            {
                m_textInput += m_event.text.text;
            }
            break;
        case SDL_KEYDOWN:
            if (m_event.type == SDL_KEYDOWN && m_event.key.keysym.sym == SDLK_BACKSPACE && m_textInput.length() > 0)
            {
                m_textInput = m_textInput.substr(0, m_textInput.length() - 1);
            }
            if (m_event.type == SDL_TEXTINPUT)
            {
                    m_textInput += m_event.text.text;
            }
            break;
        }
    }
    SDL_StartTextInput();

    m_keyboardState = SDL_GetKeyboardState(NULL);
	
    m_scroll = 0;
	
    switch (m_event.wheel.type)
    {
    case SDL_MOUSEWHEEL:
        m_scroll = m_event.wheel.y;
        break;

    default:
        break;
    }
	
    m_event.wheel = SDL_MouseWheelEvent();

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

bool InputManager::isSpacePressed()
{
    /*if (m_event.type == SDL_KEYDOWN)*/
    return m_event.type == SDL_KEYDOWN && m_event.key.keysym.sym == SDLK_SPACE;

    /*if (m_event.type == SDL_KEYDOWN && m_event.key.keysym.sym == SDLK_SPACE)
    {
        return true;
    }
    return false;*/
}

bool InputManager::isSpaceReleased()
{
    return m_event.type == SDL_KEYUP && m_event.key.keysym.sym == SDLK_SPACE;
}

string InputManager::getInputData()
{
    if (m_inputData != "")
    {
        string returnValue = m_inputData;
        m_inputData.clear();
        
        return returnValue;
    }

    return m_inputData;
}


/*
* @param prevText - the text that was alread typed
*                   this should be used for a inputField for example
*                   when you wait for new text, pass what was already
*                   in the inputField. Pass "" if nothing was typed yet.
*/
void InputManager::startTextInput(string prevText)
{
    m_textInput = prevText;

    m_textInputIsActive = true;
}

void InputManager::stopTextInput()
{
    m_textInputIsActive = false;
}

string InputManager::getTextInput()
{
    return m_textInput;
}

bool InputManager::mouseIsPressed()
{
    return m_mouseIsPressed;
}

bool InputManager::mouseIsRightPressed()
{
    return m_mouseIsRightPressed;
}

void InputManager::resetText()
{
    m_textInput = "";
}

void InputManager::setPlayerScreenPos(int2* playerScreenPos)
{
    m_playerScreenPos = playerScreenPos;
}

bool isMouseInRect(SDL_Rect rect)
{
    return MouseIsInRect(InputManager::m_mouseCoor, rect);
}

bool mouseIsRightPressed()
{
    return InputManager::mouseIsRightPressed();
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
