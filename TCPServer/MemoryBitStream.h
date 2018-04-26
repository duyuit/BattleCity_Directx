
#include <cstdint>
#include <cstdlib>
//#include "Entity.h"
#include <string>
//#include "PlayerServer.h";
//#include "Bullet.h"

namespace Define
{
	const int bitofTypePacket = 4;
	const int bitofID = 10;
	const int bitofLocation = 12;

	const int WelcomePacket = 1;
	const int UpdateCountPlayer = 2;
	const int LetStart = 3;
	const int TankPacket = 4;
	const int WorldStatePacket = 5;
	const int InputPacket = 6;

}

//
//inline uint32_t ConvertToFixed( float inNumber, float inMin, float inPrecision )
//{
//	return static_cast< int > ( ( inNumber - inMin ) / inPrecision );
//}
//
//inline float ConvertFromFixed( uint32_t inNumber, float inMin, float inPrecision )
//{
//	return static_cast< float >( inNumber ) * inPrecision + inMin;
//}


class OutputMemoryBitStream
{
public:

	OutputMemoryBitStream() :
		mBitHead(0),
		mBuffer(nullptr)
	{
		ReallocBuffer( 1500 * 8 );
	}

	~OutputMemoryBitStream()	{ free( mBuffer ); }

	void		WriteBits( uint8_t inData, uint32_t inBitCount );
	 void		WriteBits( const void* inData, uint32_t inBitCount );

	const 	char*	GetBufferPtr()		const	{ return mBuffer; }
	uint32_t		GetBitLength()		const	{ return mBitHead; }
	uint32_t		GetByteLength()		const	{ return ( mBitHead + 7 ) >> 3; }

	void WriteBytes( const void* inData, uint32_t inByteCount )	{ WriteBits( inData, inByteCount << 3 ); }


	 void Write( uint32_t inData, uint32_t inBitCount = 32 )	{ WriteBits( &inData, inBitCount ); }
	void Write( int inData, uint32_t inBitCount = 32 )		{ WriteBits( &inData, inBitCount ); }
	void Write( float inData )								{ WriteBits( &inData, 32 ); }
	
	/*void Write(Entity* pl)
	{
		Write(pl->Tag, Define::bitofID);
		Write(pl->ID, Define::bitofID);
		Write(pl->dir, Define::bitofID);
		Write((int)pl->GetPosition().x, Define::bitofLocation);
		Write((int)pl->GetPosition().y, Define::bitofLocation);
	}
	void Write(Bullet* bl)
	{
		Write(bl->ID, Define::bitofID);
		Write((int)bl->mDirect, Define::bitofID);
		Write((int)bl->GetPosition().x, Define::bitofLocation);
		Write((int)bl->GetPosition().y, Define::bitofLocation);
	}
	void Write(PlayerServer* pl)
	{
		Write(pl->ID, Define::bitofID);
		Write((int)pl->mAction, Define::bitofID);
		Write(pl->isFight);
		Write((int)pl->GetPosition().x, Define::bitofLocation);
		Write((int)pl->GetPosition().y, Define::bitofLocation);
	}*/
	
	template< typename T >
	void Write( T inData, uint32_t inBitCount = sizeof( T ) * 8 )
	{
		static_assert( std::is_arithmetic< T >::value ||
					  std::is_enum< T >::value,
					  "Generic Write only supports primitive data types" );
		WriteBits( &inData, inBitCount );
	}
	
	void 		Write( bool inData )								{ WriteBits( &inData, 1 ); }
	

	void Write( const std::string& inString )
	{
		uint32_t elementCount = static_cast< uint32_t >( inString.size() );
		Write( elementCount );
		for( const auto& element : inString )
		{
			Write( element );
		}
	}
	
private:
	void		ReallocBuffer( uint32_t inNewBitCapacity );

	char*		mBuffer;
	uint32_t	mBitHead;
	uint32_t	mBitCapacity;
};





class InputMemoryBitStream
{
public:
	
	InputMemoryBitStream( char* inBuffer, uint32_t inBitCount ) :
	mBuffer( inBuffer ),
	mBitCapacity( inBitCount ),
	mBitHead( 0 ),
	mIsBufferOwner( false ) {}
	
	InputMemoryBitStream( const InputMemoryBitStream& inOther ) :
	mBitCapacity( inOther.mBitCapacity ),
	mBitHead( inOther.mBitHead ),
	mIsBufferOwner( true )
	{
		//allocate buffer of right size
		int byteCount = ( mBitCapacity + 7 ) / 8;
		mBuffer = static_cast< char* >( malloc( byteCount ) );
		//copy
		memcpy( mBuffer, inOther.mBuffer, byteCount );
	}
	
	~InputMemoryBitStream()	{ if( mIsBufferOwner ) { free( mBuffer ); }; }
	
	const 	char*	GetBufferPtr()		const	{ return mBuffer; }
	uint32_t	GetRemainingBitCount() 	const { return mBitCapacity - mBitHead; }

	void		ReadBits( uint8_t& outData, uint32_t inBitCount );
	void		ReadBits( void* outData, uint32_t inBitCount );
	
	void		ReadBytes( void* outData, uint32_t inByteCount )		{ ReadBits( outData, inByteCount << 3 ); }

	template< typename T >
	void Read( T& inData, uint32_t inBitCount = sizeof( T ) * 8 )
	{
		static_assert( std::is_arithmetic< T >::value ||
					  std::is_enum< T >::value,
					  "Generic Read only supports primitive data types" );
		ReadBits( &inData, inBitCount );
	}
	
	void		Read( uint32_t& outData, uint32_t inBitCount = 32 )		{ ReadBits( &outData, inBitCount ); }
	void		Read( int& outData, uint32_t inBitCount = 32 )			{ ReadBits( &outData, inBitCount ); }
	void		Read( float& outData )									{ ReadBits( &outData, 32 ); }

	void		Read( uint16_t& outData, uint32_t inBitCount = 16 )		{ ReadBits( &outData, inBitCount ); }
	void		Read( int16_t& outData, uint32_t inBitCount = 16 )		{ ReadBits( &outData, inBitCount ); }

	void		Read( uint8_t& outData, uint32_t inBitCount = 8 )		{ ReadBits( &outData, inBitCount ); }
	void		Read( bool& outData )									{ ReadBits( &outData, 1 ); }
	
	/*void		Read(Entity* pl)
				{
					Read(pl->Tag, Define::bitofID);
					Read(pl->ID, Define::bitofID);
					Read(pl->dir, Define::bitofID);
					int x = 0; int y = 0; 
					Read(x, Define::bitofLocation);
					Read(y, Define::bitofLocation);
					pl->SetPosition(x, y);
				}
	void		Read(Bullet* bl)
	{
		Read(bl->ID, Define::bitofID);
		int dir = 0;
		Read(dir, Define::bitofID);
		bl->dir = (Direction)dir;
		int x = 0; int y = 0;
		Read(x, Define::bitofLocation);
		Read(y, Define::bitofLocation);
		bl->SetPosition(x, y);
	}
	void Read(PlayerServer* pl)
	{
		Read(pl->ID, Define::bitofID);
		int action = 0;
		Read(action, Define::bitofID);
		pl->mAction = (Action)action;
		Read(pl->isFight);
		int x = 0; int y = 0;
		Read(x, Define::bitofLocation);
		Read(y, Define::bitofLocation);
		pl->SetPosition(x, y);
	}*/

	void		ResetToCapacity( uint32_t inByteCapacity )				{ mBitCapacity = inByteCapacity << 3; mBitHead = 0; }


	void Read( std::string& inString )
	{
		uint32_t elementCount;
		Read( elementCount );
		inString.resize( elementCount );
		for( auto& element : inString )
		{
			Read( element );
		}
	}
private:
	char*		mBuffer;
	uint32_t	mBitHead;
	uint32_t	mBitCapacity;
	bool		mIsBufferOwner;

};

