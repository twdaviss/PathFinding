#pragma once
namespace AI 
{
	class GridBasedGraph
	{
	public:
		enum Directions
		{
			North,
			NorthEast,
			East,
			SouthEast,
			South,
			SouthWest,
			West,
			NorthWest
		};
		struct Node {
			std::array<Node*, 8> neighbours = {nullptr};
			int collumn = 0;
			int row = 0;

			Node* parent = nullptr;
			bool opened = false;
			bool closed = false;

			float cost = 0.0f;

			bool operator<(const Node& a) const
			{
				return (cost < a.cost); // (a.cost < cost)
			}
		};
		void ResetSearchParameters() const;
		void Initialize(int collumns, int rows);
		Node* GetNode(int x, int y);
		const Node* GetNode(int x, int y)const ;

		int GetCollumns() const;
		int GetRows() const;

		void SetNeighbours();
		~GridBasedGraph();
		int GetIndex(int x, int y)const;

		//int GetIndex(Node* node) const;

	private:

		std::vector<Node*> mNodes;
		int mCollumns = 0;
		int mRows = 0;


	};
}