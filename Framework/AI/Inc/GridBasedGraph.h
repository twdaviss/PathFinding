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
			std::array<Node*, 8> neighbours = {};
			int collumn = 0;
			int row = 0;
		};

		void Initialize(int collumns, int rows);
		Node* GetNode(int x, int y);
		const Node* GetNode(int x, int y)const ;

		int GetCollumns() const;
		int GetRows() const;


	private:
		int GetIndex(int x, int y)const;

		std::vector<Node*> mNodes;
		int mCollumns = 0;
		int mRows = 9;


	};
}