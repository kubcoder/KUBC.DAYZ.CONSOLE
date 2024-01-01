using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace KUBC.DAYZ.CONSOLE.Points
{
    /// <summary>
    /// Описание точки в мире
    /// </summary>
    public class Point
    {
        /// <summary>
        /// Координаты точки в мире
        /// </summary>
        public GAME.Vector Position { get; set; } = [];
        /// <summary>
        /// Ориентация игрока в мире
        /// </summary>
        public GAME.Vector Orientation { get; set; } = [];
    }
}
