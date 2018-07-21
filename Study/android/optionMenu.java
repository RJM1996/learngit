
public class OptionsMenuActivity extends Activity {
    private final static int ITEM = Menu.FIRST;

    @Override
    protected void onCreate (Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_option_menu);
    }

    // 重写 onCreateOptionsMenu() 方法添加选项菜单
    public boolean onCreateOptionsMenu(Menu menu) {
        // 添加菜单项
        menu.add(0, ITEM, 0, "开始");
        menu.add(0, ITEM + 1, 0, "退出");
        return true;
    }

    // 重写 onOptionsItemSelected() 方法, 响应选项菜单的被单击事件
    public boolean onOptionsItemSelected(MenuItem item) {
        switch (item.getItemId()) {
            case ITEM:
                // 设置 Activity 标题
                setTitle("开始游戏");
                break;
            case ITEM + 1:
                // 设置 Activity 标题
                setTitle("退出游戏");
                break;
        }
        return true;
    }
}
