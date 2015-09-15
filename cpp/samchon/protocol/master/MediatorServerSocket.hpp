#pragma once
#include <samchon/protocol/master/MediatorSocket.hpp>
#include <samchon/protocol/OneToOneServer.hpp>

namespace samchon
{
	namespace protocol
	{
		namespace master
		{
			class ExternalServerArrayMediator;

			class  MediatorServerSocket
				: public MediatorSocket,
				public virtual OneToOneServer
			{
			private:
				typedef OneToOneServer super;

			protected:
				virtual auto MY_IP() const -> std::string;
				virtual auto PORT() const -> int;

			public:
				MediatorServerSocket(ExternalServerArrayMediator*);
				virtual ~MediatorServerSocket() = default;

				virtual void start();
			};
		};
	};
};