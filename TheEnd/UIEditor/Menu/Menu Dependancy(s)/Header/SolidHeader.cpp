#include "SolidHeader.h"

SSHeader::SSHeader() :
m_Box(nullptr),
m_TextL(nullptr),
m_TextR(nullptr)
{
}

CBox& SSHeader::GetBox() {
    return *m_Box;
}

CTextUI& SSHeader::GetLeftText() {
    return *m_TextL;
}

CTextUI& SSHeader::GetRightText() {
    return *m_TextR;
}

void SSHeader::SetBox(CBox* box) {
    if (m_Box != nullptr) {
        delete m_Box;
    }
    m_Box = box;
}

void SSHeader::SetLeftText(CTextUI* left) {
    if (m_TextL != nullptr) {
        delete m_TextL;
    }
    m_TextL = left;
}

void SSHeader::SetRightText(CTextUI* right) {
    if (m_TextR != nullptr) {
        delete m_TextR;
    }
    m_TextR = right;
}

SSHeaderController::SSHeaderController():
m_Header(new SSHeader()),
m_View(new SSHeaderView())
{
}

SSHeaderController::SSHeaderController(SSHeader* header, SSHeaderView* hView):
    m_Header(header),
    m_View(hView)
{
    Init();
}

void SSHeaderController::Update() {
    m_View->Draw(&m_Header->GetBox(), &m_Header->GetLeftText(), &m_Header->GetRightText());
}

void SSHeaderController::Init() {
    if (m_Header == nullptr) {
        m_Header = new SSHeader();
    }
    if (m_View == nullptr) {
        m_View = new SSHeaderView();
    }
}
void SSHeaderController::SetPadding(float x, float y) {
    this->m_View->SetPadding(x, y);
}
CVector2 SSHeaderController::GetPadding() {
    return m_View->GetPadding();
}
void SSHeaderController::SetBox(CBox* box) {
    m_Header->SetBox(box);
}
CBox& SSHeaderController::GetBox() {
    return m_Header->GetBox();
}
CTextUI& SSHeaderController::GetTextLeft() {
    return m_Header->GetLeftText();
}
CTextUI& SSHeaderController::GetTextRight() {
    return m_Header->GetRightText();
}
void SSHeaderController::SetTextLeft(CTextUI* newText) {
    m_Header->SetLeftText(newText);
}
void SSHeaderController::SetTextRight(CTextUI* newText) {
    m_Header->SetRightText(newText);
}
SSHeaderController::~SSHeaderController() {
    if (m_Header != nullptr) {
        delete m_Header;
    }
    if (m_View != nullptr) {
        delete m_View;
    }
}
SSHeaderView::SSHeaderView() : _paddingX_(0),_paddingY_(0)
{
}
void SSHeaderView::SetPadding(float paddingX, float paddingY) {
    _paddingX_ = paddingX;
    _paddingY_ = paddingY;
}
CVector2 SSHeaderView::GetPadding() {
    return CVector2(_paddingX_, _paddingY_);
}
/*
* Within the Draw method the DrawPosition specified by m_TextL or m_TextR is the padding for the cell.
* Multi use however if you don't want padding and want it to sit on the boarder specifiy 0,0 for the Position coorindates because this has to set the position coordinates anyways.
*/
void SSHeaderView::Draw(CBox* box, CTextUI* m_TextL, CTextUI* m_TextR) {
    if (box == nullptr || m_TextL == nullptr || m_TextR == nullptr) {
        return;
    }
    m_TextR->SetTextJustification(new CRightJustify(0, box->GetCornerPos(box->BOTTOMRIGHT).x - m_TextR->pos.x));
    
    //Prereq:
    CVector2* drawLeft = new CVector2(
        (box->GetDrawPos().x - (box->GetWidth()/2) + _paddingX_) ,
        (box->GetDrawPos().y - m_TextL->CharacterHeight(0.5)) + _paddingY_);
    if (drawLeft->x > 1 || drawLeft->y > 1) {
        *drawLeft = CVector2(0.5, 0.5);
    }
    m_TextR->pos = CVector2(m_TextR->pos.x, (box->GetDrawPos().y - m_TextR->CharacterHeight(0.5)));
    m_TextL->pos = *drawLeft;


    box->Draw();
    m_TextL->Draw();
    m_TextR->Draw();
    delete drawLeft;
}
