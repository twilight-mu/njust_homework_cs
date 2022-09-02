
# coding=utf-8
import datetime
import tkinter
from tkinter import *
from tkinter.constants import *
from tkinter.ttk import Treeview, Style

from scapy.all import *   
from scapy.layers.inet import *
from scapy.layers.l2 import *



tk = tkinter.Tk()
tk.title("协议编辑器")
tk.geometry("1000x700")
# 使窗体最大化
#tk.state("zoomed")
# 左右分隔窗体
main_panedwindow = PanedWindow(tk, sashrelief=RAISED, sashwidth=5)
# 协议编辑区窗体
protocol_editor_panedwindow = PanedWindow(orient=VERTICAL, sashrelief=RAISED, sashwidth=5)
# 协议导航树
protocols_tree = Treeview()
# 当前网卡的默认网关
default_gateway = [a for a in os.popen('route print').readlines() if ' 0.0.0.0 ' in a][0].split()[-3]
# 用来终止数据包发送线程的线程事件
stop_sending = threading.Event()



# 状态栏类
class StatusBar(Frame):
    def __init__(self, master):
        Frame.__init__(self, master)
        self.label = Label(self, bd=1, relief=SUNKEN, anchor=W)
        self.label.pack(fill=X)

    def set(self, fmt, *args):
        self.label.config(text=fmt % args)
        self.label.update_idletasks()

    def clear(self):
        self.label.config(text="")
        self.label.update_idletasks()


# 状态栏
status_bar = StatusBar(tk)
status_bar.pack(side=BOTTOM, fill=X)
status_bar.set("%s", '开始')


def create_protocols_tree():
    protocols_tree.heading('#0', text='选择网络协议', anchor='w')
    # 应用层
    applicatoin_layer_tree_entry = protocols_tree.insert("", 0, "应用层", text="应用层")  # ""表示父节点是根
    http_packet_tree_entry = protocols_tree.insert(applicatoin_layer_tree_entry, 0, "HTTP包", text="HTTP包")
    dns_packet_tree_entry = protocols_tree.insert(applicatoin_layer_tree_entry, 1, "DNS包", text="DNS包")
    # 传输层
    transfer_layer_tree_entry = protocols_tree.insert("", 1, "传输层", text="传输层")
    tcp_packet_tree_entry = protocols_tree.insert(transfer_layer_tree_entry, 0, "TCP包", text="TCP包")
    upd_packet_tree_entry = protocols_tree.insert(transfer_layer_tree_entry, 1, "UDP包", text="UDP包")
    # 网络层
    ip_layer_tree_entry = protocols_tree.insert("", 2, "网络层", text="网络层")
    ip_packet_tree_entry = protocols_tree.insert(ip_layer_tree_entry, 0, "IP包", text="IP包")
    icmp_packet_tree_entry = protocols_tree.insert(ip_layer_tree_entry, 1, "ICMP包", text="ICMP包")
    arp_packet_tree_entry = protocols_tree.insert(ip_layer_tree_entry, 2, "ARP包", text="ARP包")
    # 网络接入层
    ether_layer_tree_entry = protocols_tree.insert("", 3, "网络接入层", text="网络接入层")
    mac_frame_tree_entry = protocols_tree.insert(ether_layer_tree_entry, 1, "MAC帧", text="MAC帧")
    protocols_tree.bind('<<TreeviewSelect>>', on_click_protocols_tree)
    style = Style(tk)
    disabled_bg = style.lookup("TEntry", "fieldbackground", ("disabled",))
    style.map("Treeview",
              fieldbackground=[("disabled", disabled_bg)],
              foreground=[("disabled", "gray")],
              background=[("disabled", disabled_bg)])
    protocols_tree.pack()
    return protocols_tree


def toggle_protocols_tree_state():
    """
    使protocols_tree失效
    :rtype: None
    """
    if "disabled" in protocols_tree.state():
        protocols_tree.state(("!disabled",))
        # re-enable item opening on click
        protocols_tree.unbind('<Button-1>')
    else:
        protocols_tree.state(("disabled",))
        # disable item opening on click
        protocols_tree.bind('<Button-1>', lambda event: 'break')


def on_click_protocols_tree(event):
    """
    协议导航树单击事件响应函数
    :param event: TreeView单击事件
    :return: None
    """
    selected_item = event.widget.selection()  # event.widget获取Treeview对象，调用selection获取选择对象名称
    # 清空protocol_editor_panedwindow上现有的控件
    for widget in protocol_editor_panedwindow.winfo_children():
        widget.destroy()
    # 设置状态栏
    status_bar.set("%s", selected_item[0])

    if selected_item[0] == "MAC帧":
        create_mac_sender()
    elif selected_item[0] == "ARP包":
        # pass
        create_arp_sender()
    elif selected_item[0] == "IP包":
        # pass
        create_ip_sender()
    elif selected_item[0] == "ICMP包":
        # pass
        create_icmp_sender()
    elif selected_item[0] == "TCP包":
        #pass
        create_tcp_sender()
    elif selected_item[0] == "UDP包":
        #pass
        create_udp_sender()
    elif selected_item[0] == "HTTP包":
        #pass
        create_http_sender()
    elif selected_item[0] == "DNS包":
        #pass
        create_dns_sender()


def create_protocol_editor(root, field_names):
    """
    创建协议字段编辑区
    :param root: 协议编辑区
    :param field_names: 协议字段名列表
    :return: 协议字段编辑框列表
    """
    entries = []
    for field in field_names:
        row = Frame(root)
        label = Label(row, width=15, text=field, anchor='e')
        entry = Entry(row, font=('Courier', '12', 'bold'), state='normal')  # 设置编辑框为等宽字体
        row.pack(side=TOP, fill=X, padx=5, pady=5)
        label.pack(side=LEFT)
        entry.pack(side=RIGHT, expand=YES, fill=X)
        entries.append(entry)
    return entries
def clear_protocol_editor(entries):
    """
    清空协议编辑器的当前值
    :param entries: 协议字段编辑框列表
    :return: None
    """
    for entry in entries:
        # 如果有只读Entry，也要清空它的当前值
        state = entry['state']
        entry['state'] = 'normal'
        entry.delete(0, END)
        entry['state'] = state
def create_bottom_buttons(root):
    """
    创建发送按钮和重置按钮
    :param root: 编辑编辑区
    :return: 发送按钮和清空按钮
    """
    bottom_buttons = Frame(root)
    send_packet_button = Button(bottom_buttons, width=20, text="发送")
    default_packet_button = Button(bottom_buttons, width=20, text="默认值")
    reset_button = Button(bottom_buttons, width=20, text="重置")
    bottom_buttons.pack(side=BOTTOM, fill=X, padx=5, pady=5)
    send_packet_button.grid(row=0, column=0, padx=5, pady=5)
    default_packet_button.grid(row=0, column=1, padx=2, pady=5)
    reset_button.grid(row=0, column=2, padx=5, pady=5)
    bottom_buttons.columnconfigure(0, weight=1)
    bottom_buttons.columnconfigure(1, weight=1)
    bottom_buttons.columnconfigure(2, weight=1)
    return send_packet_button, reset_button, default_packet_button

def create_mac_sender():
    """
    创建MAC帧编辑器
    :return: None
    """
    # MAC帧编辑区，字符串列表
    mac_fields = '源MAC地址：', '目标MAC地址：', '协议类型：'
    entries = create_protocol_editor(protocol_editor_panedwindow, mac_fields)
    send_packet_button, reset_button, default_packet_button = create_bottom_buttons(protocol_editor_panedwindow)
    # 为"回车键"的Press事件编写事件响应代码，发送MAC帧,绑定事件有参数必须使用lambda event:
    tk.bind('<Return>', (lambda event: send_mac_frame(entries, send_packet_button)))  # <Return>代表回车键
    # 为"发送"按钮的单击事件编写事件响应代码，发送MAC帧
    send_packet_button.bind('<Button-1>', (
        lambda event: send_mac_frame(entries, send_packet_button)))  # <Button-1>代表鼠标左键单击
    # 为"清空"按钮的单击事件编写事件响应代码，清空协议字段编辑框
    reset_button.bind('<Button-1>', (lambda event: clear_protocol_editor(entries)))
    # 为"默认值"按钮的单击事件编写事件响应代码，在协议字段编辑框填入MAC帧字段的默认值
    default_packet_button.bind('<Button-1>', (lambda event: create_default_mac_frame(entries)))
def create_default_mac_frame(entries):
    """
    在协议字段编辑框中填入默认MAC帧的字段值
    :param entries: 协议字段编辑框列表
    :return: None
    """
    clear_protocol_editor(entries)
    default_mac_frame = Ether()
    entries[0].insert(0, default_mac_frame.src)
    entries[1].insert(0, default_mac_frame.dst)
    entries[2].insert(0, hex(default_mac_frame.type))
def send_mac_frame(entries, send_packet_button):
    """
    发送MAC帧
    :param send_packet_button: MAC帧发送按钮
    :param entries:协议字段编辑框列表
    :return: None
    """
    if send_packet_button['text'] == '发送':
        mac_src = entries[0].get()
        mac_dst = entries[1].get()
        mac_type = int(entries[2].get(), 16)
        packet_to_send = Ether(src=mac_src, dst=mac_dst, type=mac_type)
        # 开一个线程用于连续发送数据包，args参数是元祖，必须放在（，）中
        t = threading.Thread(target=send_packet, args=(packet_to_send,))
        t.setDaemon(True)  # 前台界面关闭，线程即关闭
        t.start()
        # 使协议导航树不可用
        toggle_protocols_tree_state()
        send_packet_button['text'] = '停止'
    else :
        # 终止数据包发送线程
        stop_sending.set()
        # 恢复协议导航树可用
        toggle_protocols_tree_state()
        send_packet_button['text'] = '发送'

def create_arp_sender():
    """
    创建ARP包编辑器
    :return: None
    """
    # ARP包编辑区
    mac_fields = '硬件类型：', '协议类型：', '硬件地址长度：', '协议地址长度：', '操作码：', '源硬件地址：', \
                 '源逻辑地址：', '目标硬件地址：', '目标逻辑地址：'
    entries = create_protocol_editor(protocol_editor_panedwindow, mac_fields)
    send_packet_button, reset_button, default_packet_button = create_bottom_buttons(protocol_editor_panedwindow)
    # 为"回车键"的Press事件编写事件响应代码，发送ARP包
    tk.bind('<Return>', (lambda event: send_arp_packet(entries, send_packet_button)))  # <Return>代表回车键
    # 为"发送"按钮的单击事件编写事件响应代码，发送ARP包
    send_packet_button.bind('<Button-1>', (
        lambda event: send_arp_packet(entries, send_packet_button)))  # <Button-1>代表鼠标左键单击
    # 为"清空"按钮的单击事件编写事件响应代码，清空协议字段编辑框
    reset_button.bind('<Button-1>', (lambda event: clear_protocol_editor(entries)))
    # 为"默认值"按钮的单击事件编写事件响应代码，在协议字段编辑框填入ARP包字段的默认值
    default_packet_button.bind('<Button-1>', (lambda event: create_default_arp_packet(entries)))
def create_default_arp_packet(entries):
    """
    在协议字段编辑框中填入默认ARP包的字段值
    :param entries: 协议字段编辑框列表
    :return: None
    """
    clear_protocol_editor(entries)
    default_arp_packet = ARP()
    entries[0].insert(0, default_arp_packet.hwtype)
    entries[1].insert(0, hex(default_arp_packet.ptype))
    #entries[2].insert(0, default_arp_packet.hwlen)
    entries[2].insert(0, 6)
    #entries[3].insert(0, default_arp_packet.plen)
    entries[3].insert(0, 4)
    entries[4].insert(0, default_arp_packet.op)
    entries[5].insert(0, default_arp_packet.hwsrc)
    entries[6].insert(0, default_arp_packet.psrc)
    entries[7].insert(0, default_arp_packet.hwdst)
    # 目标IP地址设成本地默认网关
    entries[8].insert(0, default_gateway)
def send_arp_packet(entries, send_packet_button):
    """
    发送ARP包
    :param send_packet_button: ARP包发送按钮
    :param entries:协议字段编辑框列表
    :return: None
    """
    if send_packet_button['text'] == '发送':
        arp_hwtype = int(entries[0].get())
        arp_ptype = int(entries[1].get(),16)
        arp_hwlen = int(entries[2].get())
        arp_plen = int(entries[3].get())
        arp_op = int(entries[4].get())
        arp_hwsrc = entries[5].get()
        arp_psrc = entries[6].get()
        arp_hwdst = entries[7].get()
        arp_pdst = entries[8].get()
        packet_to_send = ARP(hwtype=arp_hwtype, ptype=arp_ptype, hwlen=arp_hwlen, plen=arp_plen,
                             op=arp_op, hwsrc=arp_hwsrc, psrc=arp_psrc, hwdst=arp_hwdst, pdst=arp_pdst)

        # 开一个线程用于连续发送数据包
        t = threading.Thread(target=send_packet, args=(packet_to_send,))
        t.setDaemon(True)
        t.start()
        # 使协议导航树不可用
        toggle_protocols_tree_state()
        send_packet_button['text'] = '停止'
    else:
        # 终止数据包发送线程
        stop_sending.set()
        # 恢复协议导航树可用
        toggle_protocols_tree_state()
        send_packet_button['text'] = '发送'

def create_ip_sender():
    """
    创建IP包编辑器
    :return: None
    """
    # IP帧编辑区
    ip_fields = 'IP协议的版本：', '首部长度(5-15)：', '区分服务：', '总长度：', '标识：', '标志(0-2)DF,MF：', \
                '片偏移：', '生存时间：', '协议(数据部分)：', '首部校验和：', '源IP地址：', '目的IP地址：'
    entries = create_protocol_editor(protocol_editor_panedwindow, ip_fields)
    send_packet_button, reset_button, default_packet_button = create_bottom_buttons(protocol_editor_panedwindow)
    # 为"回车键"的Press事件编写事件响应代码，发送ARP包
    tk.bind('<Return>', (lambda event: send_ip_packet(entries, send_packet_button)))  # <Return>代表回车键
    # 为"发送"按钮的单击事件编写事件响应代码，发送ARP包
    send_packet_button.bind('<Button-1>', (
        lambda event: send_ip_packet(entries, send_packet_button)))  # <Button-1>代表鼠标左键单击
    # 为"清空"按钮的单击事件编写事件响应代码，清空协议字段编辑框
    reset_button.bind('<Button-1>', (lambda event: clear_protocol_editor(entries)))
    # 为"默认值"按钮的单击事件编写事件响应代码，在协议字段编辑框填入ARP包字段的默认值
    default_packet_button.bind('<Button-1>', (lambda event: create_default_ip_packet(entries)))
def create_default_ip_packet(entries):
    """
        在协议字段编辑框中填入默认IP包的字段值
         :param entries: 协议字段编辑框列表
         :return: None
         """
    clear_protocol_editor(entries)
    default_ip_packet = IP()
    entries[0].insert(0, int(default_ip_packet.version))
    entries[1].insert(0, 5)
    entries[3].insert(0, 20)
    entries[2].insert(0, hex(default_ip_packet.tos))
    entries[4].insert(0, int(default_ip_packet.id))
    entries[5].insert(0, int(default_ip_packet.flags))
    entries[6].insert(0, int(default_ip_packet.frag))
    entries[7].insert(0, int(default_ip_packet.ttl))
    entries[8].insert(0, int(default_ip_packet.proto))
    entries[9]['state'] = NORMAL # 可操作
    entries[9].insert(0, "单机发送时自动计算")
    entries[9]['state'] = DISABLED  # 不可操作
    # 目标IP地址设成本地默认网关
    entries[11].insert(0, default_gateway)
    default_ip_packet = IP(dst=entries[11].get())#可以省略
    entries[10].insert(0, default_ip_packet.src)
def send_ip_packet(entries, send_packet_button):
    """
    发IP包
    :param entries:
    :param send_packet_button:
    :return:
    """
    if send_packet_button['text'] == '发送':
        ip_version = int(entries[0].get())
        ip_ihl = int(entries[1].get())
        ip_tos = int(entries[2].get(), 16)
        ip_len = int(entries[3].get())
        ip_id = int(entries[4].get())
        ip_flags = int(entries[5].get())
        ip_frag = int(entries[6].get())
        ip_ttl = int(entries[7].get())
        ip_proto = int(entries[8].get())
        ip_src = entries[10].get()
        ip_dst = entries[11].get()
        # ip_options = entries[12].get()
        packet_to_send = IP(version=ip_version, ihl=ip_ihl, tos=ip_tos, len=ip_len, id=ip_id,
                            frag=ip_frag, flags=ip_flags, ttl=ip_ttl, proto=ip_proto, src=ip_src, dst=ip_dst)
        packet_to_send = IP(raw(packet_to_send))
        entries[9]['state'] = NORMAL  # 重新激活
        entries[9].delete(0, END)
        entries[9].insert(0, hex(packet_to_send.chksum))
        entries[9]['state'] = DISABLED  # 不可操作
        # 开一个线程用于连续发送数据包
        t = threading.Thread(target=send_packet, args=(packet_to_send,))
        t.setDaemon(True)
        t.start()
        # 使协议导航树不可用
        toggle_protocols_tree_state()
        send_packet_button['text'] = '停止'
    else:
        # 终止数据包发送线程
        stop_sending.set()
        # 恢复协议导航树可用
        toggle_protocols_tree_state()
        send_packet_button['text'] = '发送'

def create_icmp_sender():
    # ICMP帧编辑区
    icmp_fields = '类型：', '代码：', '首部校验和：', '标识符：', '序列号：','源IP地址：','目的IP地址:'
    entries = create_protocol_editor(protocol_editor_panedwindow, icmp_fields)
    send_packet_button, reset_button, default_packet_button = create_bottom_buttons(protocol_editor_panedwindow)
    # 为"回车键"的Press事件编写事件响应代码，发送ARP包
    tk.bind('<Return>', (lambda event: send_icmp_packet(entries, send_packet_button)))  # <Return>代表回车键
    # 为"发送"按钮的单击事件编写事件响应代码，发送ARP包
    send_packet_button.bind('<Button-1>', (
    lambda event: send_icmp_packet(entries, send_packet_button)))  # <Button-1>代表鼠标左键单击
    # 为"清空"按钮的单击事件编写事件响应代码，清空协议字段编辑框
    reset_button.bind('<Button-1>', (lambda event: clear_protocol_editor(entries)))
    # 为"默认值"按钮的单击事件编写事件响应代码，在协议字段编辑框填入ARP包字段的默认值
    default_packet_button.bind('<Button-1>', (lambda event: create_default_icmp_packet(entries)))
def create_default_icmp_packet(entries):
    clear_protocol_editor(entries)#清空协议字段编辑框列表
    default_icmp_packet = ICMP()
    default_ip_packet= IP()
    entries[0].insert(0, int(default_icmp_packet.type))
    entries[1].insert(0, int(default_icmp_packet.code))
    entries[2]['state'] = NORMAL # 可操作
    entries[2].insert(0, "单机发送时自动计算")
    entries[2]['state'] = DISABLED  # 不可操作
    entries[3].insert(0, hex(default_icmp_packet.id))
    entries[4].insert(0, hex(default_icmp_packet.seq))
    # 目标IP地址设成本地默认网关
    entries[6].insert(0, default_gateway)
    default_ip_packet = IP(dst=entries[6].get())
    entries[5].insert(0, default_ip_packet.src)
def send_icmp_packet(entries, send_packet_button):
    if send_packet_button['text'] == '发送':
        icmp_type = int(entries[0].get())
        icmp_code = int(entries[1].get())
        icmp_id = int(entries[3].get(),16)
        icmp_seq = int(entries[4].get(),16)
        ip_src = entries[5].get()
        ip_dst = entries[6].get()
        ip=IP(src=ip_src, dst=ip_dst)
        icmp= ICMP(type=icmp_type,code=icmp_code,id=icmp_id,seq=icmp_seq)
        raw_packet=raw(ip/icmp)
        packet_to_send=IP(raw_packet)
        packet_to_send.show()
        entries[2]['state'] = NORMAL  # 重新激活
        entries[2].delete(0, END)
        entries[2].insert(0, hex(packet_to_send.chksum))
        entries[2]['state'] = DISABLED  # 不可操作
        # 开一个线程用于连续发送数据包
        t = threading.Thread(target=send_packet, args=(packet_to_send,))
        t.setDaemon(True)
        t.start()
        # 使协议导航树不可用
        toggle_protocols_tree_state()
        send_packet_button['text'] = '停止'
    else:
        # 终止数据包发送线程
        stop_sending.set()
        # 恢复协议导航树可用
        toggle_protocols_tree_state()
        send_packet_button['text'] = '发送'

def create_tcp_sender():
    """
    创建TCP包编辑器
    :return: None
    """
    # TCP帧编辑区
    tcp_fields = '源端口','目的端口','序号','确认号','数据偏移','标志位','窗口','TCP校验和',\
                 'IP协议的版本：', '首部长度：', '区分服务：','标识：', '标志(0-2)DF,MF：',\
                 '片偏移：', '生存时间：','首部校验和：', '源IP地址：', '目的IP地址：'
    entries = create_protocol_editor(protocol_editor_panedwindow, tcp_fields)
    send_packet_button, reset_button, default_packet_button = create_bottom_buttons(protocol_editor_panedwindow)
    # 为"回车键"的Press事件编写事件响应代码，发送ARP包
    tk.bind('<Return>', (lambda event: send_tcp_packet(entries, send_packet_button)))  # <Return>代表回车键
    # 为"发送"按钮的单击事件编写事件响应代码，发送ARP包
    send_packet_button.bind('<Button-1>', (
        lambda event: send_tcp_packet(entries, send_packet_button)))  # <Button-1>代表鼠标左键单击
    # 为"清空"按钮的单击事件编写事件响应代码，清空协议字段编辑框
    reset_button.bind('<Button-1>', (lambda event: clear_protocol_editor(entries)))
    # 为"默认值"按钮的单击事件编写事件响应代码，在协议字段编辑框填入TCP包字段的默认值
    default_packet_button.bind('<Button-1>', (lambda event: create_default_tcp_packet(entries)))
def create_default_tcp_packet(entries):
    """
        在协议字段编辑框中填入默认TCP包的字段值
         :param entries: 协议字段编辑框列表
         :return: None
         """
    clear_protocol_editor(entries)
    default_tcp_packet = IP()/TCP()
    entries[0].insert(0, int(default_tcp_packet.sport))
    entries[1].insert(0, int(default_tcp_packet.dport))
    entries[2].insert(0, int(default_tcp_packet.seq))
    entries[3].insert(0, int(default_tcp_packet.ack))
    entries[4].insert(0, str(default_tcp_packet.dataofs))
    entries[5].insert(0, 'S')
    entries[6].insert(0, int(default_tcp_packet.window))
    entries[7]['state'] = NORMAL # 可操作
    entries[7].insert(0, "单机发送时自动计算")
    entries[7]['state'] = DISABLED  # 不可操作

    entries[8].insert(0, int(default_tcp_packet.version))
    entries[9].insert(0, 5)
    entries[10].insert(0, hex(default_tcp_packet.tos))
    entries[11].insert(0, int(default_tcp_packet.id))
    entries[12].insert(0, int(default_tcp_packet.flags))
    entries[13].insert(0, int(default_tcp_packet.frag))
    entries[14].insert(0, int(default_tcp_packet.ttl))
    entries[15]['state'] = NORMAL # 可操作
    entries[15].insert(0, "单机发送时自动计算")
    entries[15]['state'] = DISABLED  # 不可操作
    # 目标IP地址设成本地默认网关
    entries[17].insert(0, default_gateway)
    default_ip_packet = IP(dst=entries[11].get())#可以省略
    entries[16].insert(0, default_ip_packet.src)
def send_tcp_packet(entries, send_packet_button):
    """
    发TCP包
    :param entries:
    :param send_packet_button:
    :return:
    """
    if send_packet_button['text'] == '发送':
        tcp_sport = int(entries[0].get())
        tcp_dport = int(entries[1].get())
        tcp_seq = int(entries[2].get())
        tcp_ack = int(entries[3].get())
        if entries[4].get() != 'None':
            tcp_dataofs = int(entries[4].get())
        tcp_flags = str(entries[5].get())
        tcp_window = int(entries[6].get())
        tcp=TCP(sport=tcp_sport,dport=tcp_dport,seq=tcp_seq,ack=tcp_ack,flags=tcp_flags,window=tcp_window)
        if entries[4].get() != 'None':
            tcp.dataofs = tcp_dataofs
        ip_version = int(entries[8].get())
        ip_ihl = int(entries[9].get())
        ip_tos = int(entries[10].get(), 16)
        ip_id = int(entries[11].get())
        ip_flags = int(entries[12].get())
        ip_frag = int(entries[13].get())
        ip_ttl = int(entries[14].get())
        ip_src = entries[16].get()
        ip_dst = entries[17].get()
        ip= IP(version=ip_version, ihl=ip_ihl, tos=ip_tos, id=ip_id,
                            frag=ip_frag, flags=ip_flags, ttl=ip_ttl,src=ip_src, dst=ip_dst)
        raw_packet=raw(ip/tcp)
        packet_to_send=IP(raw_packet)
        packet_to_send.show()
        #packet_to_send = IP(raw(packet_to_send))
        #tcp校验和
        #tcp=TCP(raw_packet[20:])
        tcp=packet_to_send[TCP]
        entries[7]['state'] = NORMAL  # 重新激活
        entries[7].delete(0, END)
        entries[7].insert(0, hex(tcp.chksum))
        entries[7]['state'] = DISABLED  # 不可操作
        #ip首部校验和
        entries[15]['state'] = NORMAL  # 重新激活
        entries[15].delete(0, END)
        entries[15].insert(0, hex(packet_to_send.chksum))
        entries[15]['state'] = DISABLED  # 不可操作
        # 开一个线程用于连续发送数据包
        t = threading.Thread(target=send_packet, args=(packet_to_send,))
        t.setDaemon(True)
        t.start()
        # 使协议导航树不可用
        toggle_protocols_tree_state()
        send_packet_button['text'] = '停止'
    else:
        # 终止数据包发送线程
        stop_sending.set()
        # 恢复协议导航树可用
        toggle_protocols_tree_state()
        send_packet_button['text'] = '发送'

def create_udp_sender():
    """
    创建TCP包编辑器
    :return: None
    """
    # TCP帧编辑区
    udp_fields = '源端口','目的端口','长度(最小值为8)','检验和',\
                 'IP协议的版本：', '首部长度：', '区分服务：','标识：', '标志(0-2)DF,MF：',\
                 '片偏移：', '生存时间：','首部校验和：', '源IP地址：', '目的IP地址：'
    entries = create_protocol_editor(protocol_editor_panedwindow, udp_fields)
    send_packet_button, reset_button, default_packet_button = create_bottom_buttons(protocol_editor_panedwindow)
    # 为"回车键"的Press事件编写事件响应代码，发送ARP包
    tk.bind('<Return>', (lambda event: send_udp_packet(entries, send_packet_button)))  # <Return>代表回车键
    # 为"发送"按钮的单击事件编写事件响应代码，发送ARP包
    send_packet_button.bind('<Button-1>', (
        lambda event: send_udp_packet(entries, send_packet_button)))  # <Button-1>代表鼠标左键单击
    # 为"清空"按钮的单击事件编写事件响应代码，清空协议字段编辑框
    reset_button.bind('<Button-1>', (lambda event: clear_protocol_editor(entries)))
    # 为"默认值"按钮的单击事件编写事件响应代码，在协议字段编辑框填入TCP包字段的默认值
    default_packet_button.bind('<Button-1>', (lambda event: create_default_udp_packet(entries)))
def create_default_udp_packet(entries):
    """
        在协议字段编辑框中填入默认TCP包的字段值
         :param entries: 协议字段编辑框列表
         :return: None
         """
    clear_protocol_editor(entries)
    default_udp_packet = IP()/UDP()
    entries[0].insert(0, int(default_udp_packet.sport))
    entries[1].insert(0, int(default_udp_packet.dport))
    entries[2].insert(0,8)
    entries[3]['state'] = NORMAL # 可操作
    entries[3].insert(0, "单机发送时自动计算")
    entries[3]['state'] = DISABLED  # 不可操作

    entries[4].insert(0, int(default_udp_packet.version))
    entries[5].insert(0, 5)
    entries[6].insert(0, hex(default_udp_packet.tos))
    entries[7].insert(0, int(default_udp_packet.id))
    entries[8].insert(0, int(default_udp_packet.flags))
    entries[9].insert(0, int(default_udp_packet.frag))
    entries[10].insert(0, int(default_udp_packet.ttl))
    entries[11]['state'] = NORMAL # 可操作
    entries[11].insert(0, "单机发送时自动计算")
    entries[11]['state'] = DISABLED  # 不可操作
    # 目标IP地址设成本地默认网关
    entries[13].insert(0, default_gateway)
    default_ip_packet = IP(dst=entries[13].get())#可以省略
    entries[12].insert(0, default_ip_packet.src)
def send_udp_packet(entries, send_packet_button):
    """
    发TCP包
    :param entries:
    :param send_packet_button:
    :return:
    """
    if send_packet_button['text'] == '发送':
        udp_sport = int(entries[0].get())
        udp_dport = int(entries[1].get())
        udp_len = int(entries[2].get())
        udp=UDP(sport=udp_sport,dport=udp_dport,len=udp_len)

        ip_version = int(entries[4].get())
        ip_ihl = int(entries[5].get())
        ip_tos = int(entries[6].get(), 16)
        ip_id = int(entries[7].get())
        ip_flags = int(entries[8].get())
        ip_frag = int(entries[9].get())
        ip_ttl = int(entries[10].get())
        ip_src = entries[12].get()
        ip_dst = entries[13].get()
        ip= IP(version=ip_version, ihl=ip_ihl, tos=ip_tos, id=ip_id,
                            frag=ip_frag, flags=ip_flags, ttl=ip_ttl,src=ip_src, dst=ip_dst)
        raw_packet=raw(ip/udp)
        packet_to_send=IP(raw_packet)
        packet_to_send.show()
        udp=packet_to_send[UDP]
        entries[3]['state'] = NORMAL  # 重新激活
        entries[3].delete(0, END)
        entries[3].insert(0, hex(udp.chksum))
        entries[3]['state'] = DISABLED  # 不可操作
        #ip首部校验和
        entries[11]['state'] = NORMAL  # 重新激活
        entries[11].delete(0, END)
        entries[11].insert(0, hex(packet_to_send.chksum))
        entries[11]['state'] = DISABLED  # 不可操作
        # 开一个线程用于连续发送数据包
        t = threading.Thread(target=send_packet, args=(packet_to_send,))
        t.setDaemon(True)
        t.start()
        # 使协议导航树不可用
        toggle_protocols_tree_state()
        send_packet_button['text'] = '停止'
    else:
        # 终止数据包发送线程
        stop_sending.set()
        # 恢复协议导航树可用
        toggle_protocols_tree_state()
        send_packet_button['text'] = '发送'

def create_http_sender():
    # HTTP报文编辑区
    http_fields = 'HTTP请求头','源端口：','源IP地址：','目的IP地址：'
    entries = create_protocol_editor(protocol_editor_panedwindow, http_fields)
    send_packet_button, reset_button, default_packet_button = create_bottom_buttons(protocol_editor_panedwindow)
    # 为"回车键"的Press事件编写事件响应代码，发送HTTP报文
    tk.bind('<Return>', (lambda event: send_http_packet(entries, send_packet_button)))
    # <Return>代表回车键
    # 为"发送"按钮的单击事件编写事件响应代码，发送HTTP报文
    send_packet_button.bind('<Button-1>', (lambda event: send_http_packet(entries, send_packet_button)))
    # <Button-1>代表鼠标左键单击
    # 为"清空"按钮的单击事件编写事件响应代码，清空协议字段编辑框
    reset_button.bind('<Button-1>', (lambda event: clear_protocol_editor(entries)))
    # 为"默认值"按钮的单击事件编写事件响应代码，在协议字段编辑框填入HTTP报文字段的默认值
    default_packet_button.bind('<Button-1>', (lambda event: create_default_http_packet(entries)))
def create_default_http_packet(entries):
    clear_protocol_editor(entries)
    default_http_packet = TCP()/IP()
    entries[0].insert(0, "GET/HTTP/1.1\r\n")
    entries[1].insert(0, default_http_packet.sport)
    entries[2].insert(0, default_http_packet.src)
    entries[3].insert(0, default_gateway)
def send_http_packet(entries, send_packet_button):
    if send_packet_button['text'] == '发送':
        http_options = entries[0].get()
        http_sport = int(entries[1].get())
        http_src = entries[2].get()
        http_dst = entries[3].get()
        tcp = TCP(sport=http_sport, dport=80)
        #tcp.options=http_options
        tcp.show()
        ip = IP(src=http_src, dst=http_dst)
        packet_to_send =ip/tcp/http_options
        packet_to_send.show()
        # 开一个线程用于连续发送数据报文
        t = threading.Thread(target=send_packet, args=(packet_to_send,))
        t.setDaemon(True)
        t.start()
        # 使协议导航树不可用
        toggle_protocols_tree_state()
        send_packet_button['text'] = '停止'
    else:
        # 终止数据包发送线程
        stop_sending.set()
        # 恢复协议导航树可用
        toggle_protocols_tree_state()
        send_packet_button['text'] = '发送'

def create_dns_sender():
    dns_fields = '源端口：','源IP地址：','目的IP地址：','查询/响应标志','查询方式','授权回答','可截断','期望递归','可用递归','域名','查询类型','查询类'
    entries = create_protocol_editor(protocol_editor_panedwindow, dns_fields)
    send_packet_button, reset_button, default_packet_button = create_bottom_buttons(protocol_editor_panedwindow)
    # 为"回车键"的Press事件编写事件响应代码，发送HTTP报文
    tk.bind('<Return>', (lambda event: send_dns_packet(entries, send_packet_button)))
    # <Return>代表回车键
    # 为"发送"按钮的单击事件编写事件响应代码，发送HTTP报文
    send_packet_button.bind('<Button-1>', (lambda event: send_dns_packet(entries, send_packet_button)))
    # <Button-1>代表鼠标左键单击
    # 为"清空"按钮的单击事件编写事件响应代码，清空协议字段编辑框
    reset_button.bind('<Button-1>', (lambda event: clear_protocol_editor(entries)))
    # 为"默认值"按钮的单击事件编写事件响应代码，在协议字段编辑框填入HTTP报文字段的默认值
    default_packet_button.bind('<Button-1>', (lambda event: create_default_dns_packet(entries)))
def create_default_dns_packet(entries):
    clear_protocol_editor(entries)
    default_http_packet = TCP()/IP()
    default_dns_packet=DNS()
    entries[0].insert(0, default_http_packet.sport)
    entries[1].insert(0, default_http_packet.src)
    entries[2].insert(0, default_gateway)
    entries[3].insert(0,default_dns_packet.qr)
    entries[4].insert(0,default_dns_packet.opcode)
    entries[5].insert(0,default_dns_packet.aa)
    entries[6].insert(0,default_dns_packet.tc)
    entries[7].insert(0,default_dns_packet.rd)
    entries[8].insert(0,default_dns_packet.ra)
    entries[9].insert(0,"www.baidu.com")
    entries[10].insert(0,"A")
    entries[11].insert(0,1)
def send_dns_packet(entries, send_packet_button):
    if send_packet_button['text'] == '发送':
        dns_sport = int(entries[0].get())
        dns_src = entries[1].get()
        dns_dst = entries[2].get()
        dns_qr =int(entries[3].get())
        dns_opcode = int(entries[4].get())
        dns_aa = int(entries[5].get())
        dns_tc = int(entries[6].get())
        dns_rd = int(entries[7].get())
        dns_ra = int(entries[8].get())
        dns_qname = entries[9].get()
        dns_qtype = entries[10].get()
        dns_qclass = int(entries[11].get())
        udp = UDP(dport=dns_sport)
        #tcp.options=http_options
        ip = IP(src=dns_src, dst=dns_dst)
        dns=DNS(id=1,qr=dns_qr,opcode=dns_opcode,aa=dns_aa,tc=dns_tc,rd=dns_rd,ra=dns_ra)
        dns.qd=DNSQR(qname=dns_qname,qtype=dns_qtype,qclass=dns_qclass)
        packet_to_send =ip/udp/dns
        packet_to_send.show()
        # 开一个线程用于连续发送数据报文
        t = threading.Thread(target=send_packet, args=(packet_to_send,))
        t.setDaemon(True)
        t.start()
        # 使协议导航树不可用
        toggle_protocols_tree_state()
        send_packet_button['text'] = '停止'
    else:
        # 终止数据包发送线程
        stop_sending.set()
        # 恢复协议导航树可用
        toggle_protocols_tree_state()
        send_packet_button['text'] = '发送'

def send_packet(packet_to_send):
    n = 0# 对发送的数据包次数进行计数，用于计算发送速度
    stop_sending.clear()
    packet_size = len(packet_to_send)# 待发送数据包的长度（用于计算发送速度）
    # 推导数据包的协议类型
    proto_names = ['DNS','HTTP','TCP', 'UDP', 'ICMP', 'IP', 'ARP', 'MAC','Ether', 'Unknown']
    packet_proto = ''
    for pn in proto_names:
        if pn in packet_to_send:
            packet_proto = pn
            break
    # 开始发送时间点
    begin_time = datetime.now()
    while not stop_sending.is_set():
        if isinstance(packet_to_send, Ether):
            sendp(packet_to_send, verbose=0)  # verbose=0,不在控制回显'Sent 1 packets'.
        else:
            send(packet_to_send, verbose=0)
        n += 1
        end_time = datetime.now()
        total_bytes = packet_size * n
        #修改
        total_time = (end_time - begin_time).total_seconds()
        if total_time == 0:
            total_time = 2.23E-308  # 当begin_time和end_time相等时，将total_time设为IEEE 745标准中规定的最小浮点数
        bytes_per_second = total_bytes / total_time / 1024
        # bytes_per_second = total_bytes / ((end_time - begin_time).total_seconds()) / 1024
        status_bar.set('已经发送了%d个%s数据包, 已经发送了%d个字节，发送速率: %0.2fK字节/秒',
                       n, packet_proto, total_bytes, bytes_per_second)


def create_welcome_page(root):
    welcome_string = '网络编程大作业\n发包器\n学号：919106840333\n姓名：孙傲歆'
    Label(root, justify=CENTER, padx=10, pady=150, text=welcome_string,
          font=('隶书', '30', 'bold')).pack()


if __name__ == '__main__':
    # 创建协议导航树并放到左右分隔窗体的左侧
    main_panedwindow.add(create_protocols_tree())
    # 将协议编辑区窗体放到左右分隔窗体的右侧
    main_panedwindow.add(protocol_editor_panedwindow)
    # 创建欢迎界面
    create_welcome_page(protocol_editor_panedwindow)
    
    main_panedwindow.pack(fill=BOTH, expand=1)
    # 启动消息处理
    tk.mainloop()
