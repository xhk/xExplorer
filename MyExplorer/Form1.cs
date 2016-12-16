using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;


namespace WindowsFormsApplication1
{
    public partial class Form1 : Form
    {
        private HtmlDocument m_doc;
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            //webBrowser1.Navigate("file:///D:/git_hub_prj/xExplorer/js/test.htm");
            textBoxUrl.Text = "http://www.ichinachess.com/forum.php?mod=post&action=newthread&fid=41";
        }

        private void webBrowser1_DocumentCompleted(object sender, WebBrowserDocumentCompletedEventArgs e)
        {
            HtmlDocument doc =  webBrowser1.Document;
            HtmlElementCollection hc = doc.GetElementsByTagName("input");
            
            foreach( HtmlElement he in hc)
            {
                //he.InnerText = ("aaaaaaaaaaa");
            }

            hc = doc.GetElementsByTagName("head");
            var head = hc[0];
            var se = doc.CreateElement("script");
            //se.SetAttribute("src", "file:///D:/git_hub_prj/xExplorer/js/test.js");
            //head.InsertAdjacentElement(HtmlElementInsertionOrientation.BeforeEnd,se);

           
            
        }

        private void buttonStart_Click(object sender, EventArgs e)
        {
            var url = textBoxUrl.Text;
            webBrowser1.Navigate(url);


        }

        private void buttonTest_Click(object sender, EventArgs e)
        {
            HtmlDocument doc = webBrowser1.Document;
            HtmlElement subject = doc.GetElementById("subject");
            String val = "Test";
            subject.SetAttribute("value", val);

            HtmlElement frame = doc.GetElementById("e_iframe");
            var taDoc = doc.Window.Frames["e_iframe"].Document;
            var ta = taDoc.GetElementsByTagName("body");
            ta[0].InnerText = "Test";

            var submit = doc.GetElementById("postsubmit");
            submit.InvokeMember("click");

        }
    }
}
