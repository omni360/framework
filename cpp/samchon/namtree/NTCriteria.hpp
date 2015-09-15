#pragma once
#include <samchon/protocol/SharedEntityArray.hpp>

namespace samchon
{
	namespace namtree
	{
		class NTFactory;
		class NTSide;

		class NTIterator;

		/**
		 * @brief Criteria, a conditional expression with weight
		 *
		 * @details
		 * <p> NTCriteria is an object to realize ANN(Artificial Neural Network). </p>
		 * <p> You can make the ANN model having weight and bias. </p>
		 *
		 * <ol>
		 *	<li> A conditional expression with weight </li>
		 *		<p> F(x) = (NTSide < NTSide ? 1: 0) X weight </p>
		 *		<p> NTCrietria is made up for conditional expression. </p>
		 *		<ul>
		 *			<li> When the expression is true, returns 1 * weight </li>
		 *			<li> When the expression is false, returns 0 </li>
		 *		</ul>
		 *
		 *	<li> Hierarchical relationship </li>
		 *		<ul>
		 *			<li> In vertical relationship: multiply (X) </li>
		 *			<li> In horizontal relationship: plus (+) </li>
		 *		</ul>
		 *		<p> With that rule, you can make enormous conditions. I can sure 
		 *		there's not any condition can'be be expressed by the model. </p>
		 *
		 *	<li> Making bias </li>
		 *		<p> Just make a NTCriteria returns only true. </p>
		 *		<p> It's the bias returns only weight. </p>
		 *
		 *	<li> Explore </li>
		 *	<ol>
		 *		<li> Exporing in a NTCriteria (optimize a side) </li>
		 *			<p> Make a NTSide to be nullptr, then NTCriteria will explore the best value.</p>
		 *			<p> Nam-Tree will calculate the condtions from minimum to maximum in INTExplore
		 *			reach to the precision, by the method of multi-demensional grid. </p>
		 *
		 *		<li> Exploring parameter in NTSide </li>
		 *			<p> If you set the parameterMNap to be empty, Nam-Tree will explore the best parameter 
		 *			until reach to the precision in INTExploreParameter from minimum to maximum. </p>
		 *
		 *		<li> Exploring by creating NTCriteria </li>
		 *			<p> (Creates lots of hierarchical conditions and tests them) </p>
		 *			<p> If all the side (left and right) in a NTCriteria are nullptr, the NTCriteria
		 *			will make a lot of children NTCriteria(s) to test lots of cases, so that derives
		 *			the best condition set will be made up. </p>
		 *			<p> This process will ride on same routines of 4-1 and 4-2, for each created
		 *			cases. Of course, this process needs too much time, so that you may need to be
		 *			patient. </p>
		 *	</ol>
		 * </ol>
		 *
		 * @author Jeongho Nam
		 */
		class  NTCriteria
			: public virtual protocol::SharedEntityArray
		{
		private:
			typedef protocol::SharedEntityArray super;

		public:
			virtual auto TAG() const -> std::string override;
			virtual auto CHILD_TAG() const -> std::string override;

			enum
			{
				LESS = -2,
				LESS_EQUAL = -1,
				EUQLA = 0,
				LARGER_EQUAL = 1,
				LARGER = 2
			};

		protected:
			NTFactory *factory;
			NTCriteria *parent;
			
			NTSide *leftSide;
			NTSide *rightSide;
			
			int operator_;
			double weight;

		public:
			NTCriteria(NTFactory*, NTCriteria*);
			virtual ~NTCriteria();

			virtual void construct(std::shared_ptr<library::XML>) override;
			SHARED_ENTITY_ARRAY_ELEMENT_ACCESSOR_HEADER(NTCriteria)

		protected:
			virtual auto createChild(std::shared_ptr<library::XML>) -> protocol::Entity* override;

		public:
			virtual void initRetrieve();
			auto calcRetrieved(NTIterator&) const -> double;
			
			virtual auto toXML() const -> std::shared_ptr<library::XML> override;
		};
	};
};