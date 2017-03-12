#include "StdAfx.h"
#include "MRGLView.h"

void print_query_info(point3d query, OcTreeNode* node) {
	if (node != NULL) {
		cout << "occupancy probability at " << query << ":\t " << node->getOccupancy() << endl;
	}
	else
		cout << "occupancy probability at " << query << ":\t is unknown" << endl;
}


CMRGLView::CMRGLView(void)
{

}

CMRGLView::~CMRGLView(void)
{

}


void CMRGLView::DrawGL()
{
	//요걸 쓰면 그냥 빨간 구만 나오고, 
	CGLView::DrawGL();
	//필요하면 재정의 해서 쓰고...

}

void	CMRGLView::TestOctomap()
{
	cout << "[Octomap Test]" << endl;

	cout << endl;
	cout << "generating example map" << endl;

	OcTree tree(0.1);  // create empty tree with resolution 0.1


					   // insert some measurements of occupied cells

	for (int x = -20; x<20; x++) {
		for (int y = -20; y<20; y++) {
			for (int z = -20; z<20; z++) {
				point3d endpoint((float)x*0.05f, (float)y*0.05f, (float)z*0.05f);
				tree.updateNode(endpoint, true); // integrate 'occupied' measurement
			}
		}
	}

	// insert some measurements of free cells

	for (int x = -30; x<30; x++) {
		for (int y = -30; y<30; y++) {
			for (int z = -30; z<30; z++) {
				point3d endpoint((float)x*0.02f - 1.0f, (float)y*0.02f - 1.0f, (float)z*0.02f - 1.0f);
				tree.updateNode(endpoint, false);  // integrate 'free' measurement
			}
		}
	}

	cout << endl;
	cout << "performing some queries:" << endl;

	point3d query(0., 0., 0.);
	OcTreeNode* result = tree.search(query);
	print_query_info(query, result);

	query = point3d(-1., -1., -1.);
	result = tree.search(query);
	print_query_info(query, result);

	query = point3d(1., 1., 1.);
	result = tree.search(query);
	print_query_info(query, result);


	cout << endl;
	tree.writeBinary("simple_tree.bt");
	cout << "wrote example file simple_tree.bt" << endl << endl;
	cout << "now you can use octovis to visualize: octovis simple_tree.bt" << endl;
	cout << "Hint: hit 'F'-key in viewer to see the freespace" << endl << endl;

}