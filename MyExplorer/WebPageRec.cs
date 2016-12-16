using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsFormsApplication1
{

    class CssSelector
    {
        public CssSelector(String s)
        {
            var space_pos = s.IndexOf(" ");
            if( space_pos != -1)
            {
                s = s.Substring(0, space_pos);
                next = s.Substring(space_pos + 1);       
            }

            
        }

        public String id { get; }
        public String tag { get; }
        public List<String> css_list { get; }

        public String next { get; }

    }

    // style from recognize
    class Style
    {
        List<String> urlContians;
        List<String> selectorList;

        public Boolean Match(String url, HtmlDocument doc)
        {
            if( urlContians.Count>0)
            {
                foreach(String s in urlContians)
                {
                    if( url.IndexOf(s)==-1)
                    {
                        return false;
                    }
                }
            }

            foreach(String s in selectorList)
            {

            }

            return true;
        }

        
    }
    class WebPageRec
    {
        public WebPageRec()
        {

        }

        public void Rec(String url, HtmlDocument doc)
        {
            
        }
    }
}
