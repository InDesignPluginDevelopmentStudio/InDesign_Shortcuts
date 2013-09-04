#ifndef __IDSC_TREENODEBASE_H__
#define __IDSC_TREENODEBASE_H__

#include <list>
#include <PMString.h>

#ifdef MACINTOSH
#include "IPMStream.h"
#endif


template <class T>
class TreeNodeBase
{
public:
	TreeNodeBase() :
		_pParent(nil),
		_name(kNullString),
		_uid(kInvalidUID)
	{
	}

	virtual ~TreeNodeBase()
	{
	}

	TreeNodeBase(const TreeNodeBase& rhs) :
		_pParent(0)
	{
		DeepCopy(rhs);
	}

	TreeNodeBase& operator=(const TreeNodeBase& rhs)
	{
		if( this != & rhs )
			DeepCopy(rhs);
		return *this;
	}

	bool operator==(const TreeNodeBase& rhs) const
	{
		return _uid == rhs._uid;
	}

	T* GetNthChild(int32 indexInParent) const
	{
		if( _children.size() > indexInParent )
		{
			typename std::list<T>::const_iterator iter = _children.begin();
			ASSERT( indexInParent < _children.size() );
			advance( iter, indexInParent );
			return const_cast<T*>( &( *iter ) );
		}
		return nil;
	}

	T* GetParent() const 
	{ 
		return _pParent; 
	}

	int32 ChildCount() const
	{
		int32 n = (int32)this->_children.size();
		return n;
	}

	PMString GetName() const
	{
		return this->_name;
	}

	UID  GetUID() const
	{
		return this->_uid;
	}

	UID GetParentUID() const
	{
		return this->_parentUID;
	}

	const T* AddChild(const T& o)
	{
		this->_children.push_back( o );
		return &( *_children.rbegin() );
	}

	const T* InsertChild(const T& o,int32 idx)
	{
		typename std::list<T>::iterator where=this->_children.begin();
		while(idx--)
			where++;
		typename std::list<T>::iterator newO=this->_children.insert(where,o);
		return &( *newO );
	}

	void RemoveChild(const T& o)
	{
		typename std::list<T>::iterator result = std::find(_children.begin(), 
		_children.end(), o);

		if(result != _children.end())
		{
			_children.erase(result);
		}
	}

	void SetParent(const T* p)
	{
		this->_pParent = const_cast<T*>( p );
	}

	void SetName(const PMString& name)
	{
//		if( name.IsTranslatable() ) 
//			name.Translate();
		this->_name = name;
		this->_name.SetTranslatable(kFalse);	
	}

	void SetUID(UID uid)
	{
		this->_uid = uid;
	}

	
	void DeleteChild( T* pNode )
	{
		/*/ XPR-26579 - [Regression] [Mac] Search item in Data Schema panel , indesign crash.
		// It has problem if use the object that get from fChildren to do remove on MAC, 
		// use a copy to instead.
		fChildren.remove( *pNode );
		/*/
		T node = *pNode;
		_children.remove( node );
		//*/
	}

	int32 CountNodeNum()
	{
		int32 nNum = 0;
		CountNodeNum( nNum );
		return nNum;
	}

	void OutToStream( IPMStream* stream )
	{
		int32 uid = _uid.Get();
		stream->XferInt32( uid );
		int32 parUid = _pParent ? _pParent->GetUID().Get() : 0;
		stream->XferInt32( parUid );
		_name.ReadWrite( stream );
	}

	int32 IndexOfParent()
	{
		for( int32 i = 0; i < _pParent->ChildCount(); ++i )
		{
			if( _pParent->GetNthChild( i ) == this )
				return i;
		}
		return -1;
	}

	bool16 IsRoot()
	{
		return _uid == kInvalidUID + 1;
	}

	template <class U> void WalkNode( U& functor )
	{
		T* p = ( T* )this;
		functor( p );
		typename std::list<T>::iterator iter = _children.begin();
		typename std::list<T>::iterator end = _children.end();
		while( iter != end )
		{
			( *iter ).WalkNode( functor );
			++iter;
		}
	}

	template <class U> bool16 DeleteMatchedNode( U& functor )
	{
		T* p = ( T* )this;
		
		if( _children.size() == 0 )
			return functor( p );

		typename std::list<T>::iterator iter = _children.begin();
		typename std::list<T>::iterator end = _children.end();
		while( iter != end )
		{
			if( iter->DeleteMatchedNode( functor ) )
				iter = _children.erase( iter );
			else
				++iter;
		}
		if( _children.size() == 0 )
			return functor( p );
		else
			return kFalse;
	}


	template <class U> bool16 WalkNodeEx( U& functor )
	{
		T* p = ( T* )this;
		bool16 bRet = functor( p );
		if( bRet )
			return bRet;

		typename std::list<T>::iterator iter = _children.begin();
		typename std::list<T>::iterator end = _children.end();
		while( iter != end )
		{
			bRet = ( *iter ).WalkNodeEx( functor );
			if( bRet ) 
				return bRet;
			++iter;
		}
		return kFalse;
	}


	template <class U, class V> void WalkNode( U& prefunctor, V& postfunctor )
	{
		T* p = ( T* )this;
		prefunctor( p );
		typename std::list<T>::iterator iter = _children.begin();
		typename std::list<T>::iterator end = _children.end();
		while( iter != end )
		{
			( *iter ).WalkNode( prefunctor, postfunctor );
			++iter;
		}
		postfunctor( p );
	}

	bool16 IsValidUID( UID uid )
	{
		if( uid == _uid )
			return kTrue;

		typename std::list<T>::iterator iter = _children.begin();
		typename std::list<T>::iterator end = _children.end();
		for( ; iter != end; ++iter )
		{
			if( iter->IsValidUID( uid ) )
				return kTrue;
		}

		return kFalse;
	}
	int32 GetLevel()
	{
		return _pParent ? _pParent->GetLevel() + 1 : 0;
	}

	void ClearChildren()
	{
		_children.clear();
	}

private:
	void DeepCopy(const TreeNodeBase& rhs)
	{
		this->_children.clear();
		this->_children.assign( rhs.fChildren.begin(), rhs.fChildren.end() );
		this->_pParent = rhs.fParent;
		this->_name = rhs.fNodeName;
		this->_uid = rhs.fNodeUID;
	}

	void CountNodeNum( int32& nNum )
	{
		++nNum;
		typename std::list<T>::iterator iter = _children.begin();
		typename std::list<T>::iterator end = _children.end();
		for( ; iter != end; ++iter )
			iter->CountNodeNum( nNum );
	}

protected:
	UID _uid;
	PMString _name;
	T* _pParent;
	std::list<T> _children;
	UID _parentUID;
};

#endif
