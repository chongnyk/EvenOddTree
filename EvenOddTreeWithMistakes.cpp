/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    int treeHeight(TreeNode* node) {
        if(node == nullptr){
            return 0;
        }
        else {
            int lHeight = treeHeight(node->left);
            int rHeight = treeHeight(node->right);
            if(lHeight >= rHeight){
                return lHeight + 1;
            }
            else {
                return rHeight + 1;
            }
        }
    }

    void appendCurrentLevel(int index, vector<vector<TreeNode*>>& levels){
        for(TreeNode* node : levels[index - 1]){
            if(node->left != nullptr){
                levels[index].push_back(node->left);
            }

            if(node->right != nullptr){
                levels[index].push_back(node->right);
            }
        }
    }

    bool isEvenOddTree(TreeNode* root) {
        int height = treeHeight(root);
        vector<vector<TreeNode*>> levels(height);
        levels[0].push_back(root);
        bool flag = true;

        for(int idx = 1; idx < height; idx++){
            appendCurrentLevel(idx, levels);
        }

        int ctr = 0;
        for(vector<TreeNode*> level : levels){
            int k = 1;
            if(ctr % 2 == 1){
                reverse(level.begin(), level.end());
                k = 0;
            }
            //for debugging
            /*
            for(TreeNode* node : level){
                cout << node->val << ' ';
            }
            cout << '\n';
            */
            ctr++;

            if (adjacent_find(level.begin(), level.end(), [](TreeNode* lhs, TreeNode* rhs){
                return lhs->val >= rhs->val;
            }) == level.end() && all_of(level.begin(), level.end(), [k](TreeNode* node){
                return node->val % 2 == k;
            })){
                cout << "adjacent pass at level " << ctr << " and all odd/even" << '\n';
            }
            else {
                cout << "no pass at level " << ctr << '\n';
                flag = false;
            }
        }
        return flag;

        //the below does not work because adjacent_find and all_of have strange interactions when applied to vectors in vectors via indices' direct access
        //it is remedied by using a foreach loop above instead of looping by direct index access
        /*
        for(int j = 0; j < height; j++ && flag == true){
            int k = (j % 2 == 0) ? 1 : 0;
            if (adjacent_find(levels[j].begin(), 
                              levels[j].end(), 
                              [](TreeNode* lhs, TreeNode* rhs){
                                    return lhs->val >= rhs->val;
                              }) == levels[j].end() 
                && all_of(levels[j].begin(),
                          levels[j].end(),
                          [k](TreeNode* node){
                                return (node->val % 2 == k);
                })){
                continue;
            }
            else {
                flag = false;
                cout << "False at " << j << '\n';
            }
        }
        */

        //the below did not work for a vector of vectors, reason unclear, do not attempt this in the future
        /*
        return all_of(levels.cbegin(), levels.cend(), [](vector<TreeNode*> level){
            return (adjacent_find(level.begin(), level.end(), [](TreeNode* lhs, TreeNode* rhs){
                return lhs->val >= rhs->val;
            }) == level.end());
        });
        */
        //cout << height << '\n' << levels.size() << '\n';
        //return true;
    }
};
