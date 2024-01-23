#include "GameObject.h"
#include "Direct3D.h"
#include "Transform.h"
#include "SphereCollider.h"
GameObject::GameObject():pParent_(nullptr),pCollider_(nullptr),IsDead(false)
{
}

GameObject::GameObject(GameObject* parent, const std::string& name): pParent_(parent),
objectName_(name),IsDead(false)
{
	if (parent != nullptr)
		this->transform_.pParent_ = &(parent->transform_);
}


GameObject::~GameObject()
{
}

// 削除するかどうか
//bool GameObject::IsDead()
//{
//	return (state_.dead != 0);
//}

// 自分を削除する
void GameObject::KillMe()
{
	IsDead = true;
}




void GameObject::UpdateSub()
{
	Update();

	RoundRobin(GetRootJob());

	for (auto itr = childList_.begin(); itr != childList_.end();itr++ )
	{
		(*itr)->UpdateSub();
	}
	for (auto itr = childList_.begin(); itr != childList_.end();)
	{
		if ((*itr)->IsDead == true)
		{
			ReleaseSub();
			SAFE_DELETE(*itr);
			itr = childList_.erase(itr);
		}
		else {
			itr++;
		}
	}
}

void GameObject::DrawSub()
{
	Draw();
	for (auto itr = childList_.begin(); itr != childList_.end(); itr++)
		(*itr)->DrawSub();
}

void GameObject::ReleaseSub()
{

	for (auto itr = childList_.begin(); itr != childList_.end(); itr++) {
		(*itr)->ReleaseSub();
	}
	Release();
}

void GameObject::SetScale(XMFLOAT3 scl_)
{
	transform_.scale_ = scl_;
}

void GameObject::SetPosition(XMFLOAT3 pos_)
{
	transform_.position_ = pos_;
}

GameObject* GameObject::FindChildObject(string _objName)
{
	if (_objName == this->objectName_) {
		return(this);
	}
	else {
		//for (auto itr = childList_.begin(); itr != childList_.end(); itr++) 
		for(auto itr: childList_)
		{
			GameObject* obj = itr->FindChildObject(_objName);
			if (obj != nullptr)
				return obj;
		}
	}
	return nullptr;
}
/// <summary>
///		再帰呼び出しでROOTJOB探して返すやーつ
/// </summary>
/// <returns></returns>RootJobのアドレス
GameObject* GameObject::GetRootJob()
{
	if (pParent_ == nullptr)
		return this;

	return pParent_->GetRootJob();
}

GameObject* GameObject::FindObject(string _objName)
{
	return GetRootJob()->FindChildObject(_objName);
}

void GameObject::AddCollider(SphereCollider* pCollider)
{
	this->pCollider_ = pCollider;
}

void GameObject::Collision(GameObject* pTarget)
{
	if (pTarget == this || pTarget->pCollider_ == nullptr) {
		return;
	}

	/*XMVECTOR v{ transform_.position_.x - pTarget->transform_.position_.x,
				transform_.position_.y - pTarget->transform_.position_.y,
				transform_.position_.z - pTarget->transform_.position_.z,
				0};
	XMVECTOR dist = XMVector3Dot(v, v);*/

	float dist = (transform_.position_.x - pTarget->transform_.position_.x) * (transform_.position_.x - pTarget->transform_.position_.x)
		+ (transform_.position_.y - pTarget->transform_.position_.y) * (transform_.position_.y - pTarget->transform_.position_.y)
		+ (transform_.position_.z - pTarget->transform_.position_.z) * (transform_.position_.z - pTarget->transform_.position_.z);
	float rDist = (this->pCollider_->GetRadius() + pTarget->pCollider_->GetRadius() * (this->pCollider_->GetRadius() + pTarget->pCollider_->GetRadius()));

	if (dist <= rDist) {
		//double p = 0;
		OnCollision(pTarget);
	}

}
void GameObject::OnCollision(GameObject* pTarget)
{

}


void GameObject::RoundRobin(GameObject* pTarget)
{
	if (pCollider_ == nullptr) 
		return;
	
	if (pTarget->pCollider_ != nullptr) 
		Collision(pTarget);
	
	if (pTarget->pCollider_ != nullptr)
		OnCollision(pTarget);

	for (auto itr = pTarget->childList_.begin(); itr != pTarget->childList_.end(); itr++)
		RoundRobin(*itr);
	
}







