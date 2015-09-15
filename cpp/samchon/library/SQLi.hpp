#pragma once

#include <memory>
#include <mutex>
#include <string>

namespace samchon
{
	namespace library
	{
		class SQLStatement;

		/**
		 * @brief SQL interface; DBMS connector
		 *
		 * @details SQLi is an utility class for connecting to the DBMS
		 * 
		 * @author Jeongho Nam
		 */
		class  SQLi
		{
		friend class SQLStatement;
		
		protected:
			/**
			 * @brief Driver; name of DBMS used for connection
			 *
			 * @details
			 *  \li MySQL: \"{MySQL Server}\"
			 *	\li MS-SQL: \"{SQL Server}\"
			 *	\li PL-SQL: \"{Oracle}\"
			 */
			std::string driver;

			/**
			 * @brief Port number of DBMS
			 *
			 * @details
			 *	\li MySQL: 3306 
			 *	\li MS-SQL: 1433
			 *	\li PL-SQL: 1521
			 */
			int port;

			/**
			 * 
			 */
			virtual auto getErrorMessage(short type) const -> std::string;

		private:
			/**
			 * @brief Handler of DB-connector
			 */
			void *hdbc;

			/**
			 * @brief SQLStatement's pointer linked with the SQLi
			 */
			SQLStatement *stmt;

			/**
			 * @brief Mutex ensuring concurrency with SQLStatement
			 */
			std::mutex stmtMutex;

		public:
			/**
			 * @brief Construct from driver name and port
			 *
			 * @param driver Driver name of DBMS
			 * @param port Port number of DBMS
			 */
			SQLi(const std::string &driver, int port);
			virtual ~SQLi();

			/**
			 * @brief Connect to the DBMS\n
			 * 
			 * @param ip An IP address of the DBMS
			 * @param db A name of database to access
			 * @param id Your own ID authorified from DBMS
			 * @param pwd A password for the ID
			 *
			 * @throw exception Error message from DBMS
			 */
			virtual void connect
			(
				const std::string &ip, const std::string &db,
				const std::string &id, const std::string &pwd
			);

			/**
			 * @brief Disconnect from DBMS
			 */
			virtual void disconnect();

			/**
			 * @brief Factory method for creating SQLStatement
			 *
			 * @details
			 * Recommend to create SQLStatement by this method.
			 * Direct creation is not recommended as the reason of domain problem of each DBMS
			 * 
			 * @return A SQLStatement matched for the domain SQLi
			 */
			virtual auto createStatement() -> std::shared_ptr<SQLStatement>;
		};
	};
};